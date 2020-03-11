/****************************************************************************
 * examples/myapp/myapp_main.c
 *
 *   Copyright (C) 2008, 2011-2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <debug.h>
#include <sys/boardctl.h>

#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>


/****************************************************************************
 * CONSTANTS
 ****************************************************************************/

#ifndef CONFIG_ADC
#  error "ADC device support is not enabled (CONFIG_ADC)"
#endif



#ifndef CONFIG_EXAMPLES_ADC_NSAMPLES
#  define CONFIG_EXAMPLES_ADC_NSAMPLES 4
#endif


#ifndef CONFIG_EXAMPLES_ADC_DEVPATH
#  define CONFIG_EXAMPLES_ADC_DEVPATH "/dev/adc0"
#endif

#ifndef CONFIG_EXAMPLES_ADC_GROUPSIZE
#  define CONFIG_EXAMPLES_ADC_GROUPSIZE 1
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/


static struct adc_state_s g_adcstate;


/****************************************************************************
 * Data types
 ****************************************************************************/

struct adc_state_s
{
  bool      initialized;
  FAR char *devpath;
  int       count;
};


/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: adc_devpath
 ****************************************************************************/

static void adc_devpath(FAR struct adc_state_s *adc, FAR const char *devpath)
{
  /* Get rid of any old device path */

  if (adc->devpath)
    {
      free(adc->devpath);
    }

  /* Then set-up the new device path by copying the string */

  adc->devpath = strdup(devpath);
}


/****************************************************************************
 * myapp_main
 ****************************************************************************/

#if defined(BUILD_MODULE)
int main(int argc, FAR char *argv[])
#else
int myapp_main(int argc, char *argv[])
#endif
{

  struct adc_msg_s sample[CONFIG_EXAMPLES_ADC_GROUPSIZE];
  size_t readsize;
  ssize_t nbytes;
  int fd;
  int errval = 0;
  int ret;
  int i;

  UNUSED(ret);

  printf("Myapp running!!\n");

  (void)boardctl(BOARDIOC_INIT, 0);


  /* Check if we have initialized */

  if (!g_adcstate.initialized)
    {
      /* Initialization of the ADC hardware must be performed by board-specific
       * logic prior to running this test.
       */

      /* Set the default values */

      adc_devpath(&g_adcstate, CONFIG_EXAMPLES_ADC_DEVPATH);

      g_adcstate.initialized = true;
    }

#if CONFIG_EXAMPLES_ADC_NSAMPLES > 0
  g_adcstate.count = CONFIG_EXAMPLES_ADC_NSAMPLES;
#else
  g_adcstate.count = 1;
#endif


  /* Open the ADC device for reading */

  printf("adc_main: Hardware initialized. Opening the ADC device: %s\n", g_adcstate.devpath);

  fd = open(g_adcstate.devpath, O_RDONLY);
  if (fd < 0)
    {
      printf("adc_main: open %s failed: %d\n", g_adcstate.devpath, errno);
      errval = 2;
      goto errout;
    }

  /* Now loop the appropriate number of times, displaying the collected
   * ADC samples.
   */

  for (g_adcstate.count = 0; g_adcstate.count < CONFIG_EXAMPLES_ADC_NSAMPLES; g_adcstate.count++)
  {
    /* Flush any output before the loop entered or from the previous pass
     * through the loop.
     */

    fflush(stdout);

#ifdef CONFIG_EXAMPLES_ADC_SWTRIG
    /* Issue the software trigger to start ADC conversion */

    ret = ioctl(fd, ANIOC_TRIGGER, 0);
    if (ret < 0)
      {
        int errcode = errno;
        printf("adc_main: ANIOC_TRIGGER ioctl failed: %d\n", errcode);
      }
#endif

    /* Read up to CONFIG_EXAMPLES_ADC_GROUPSIZE samples */

    readsize = CONFIG_EXAMPLES_ADC_GROUPSIZE * sizeof(struct adc_msg_s);
    nbytes = read(fd, sample, readsize);

    /* Handle unexpected return values */

    if (nbytes < 0)
      {
        errval = errno;
        if (errval != EINTR)
          {
            printf("adc_main: read %s failed: %d\n",
                   g_adcstate.devpath, errval);
            errval = 3;
            goto errout_with_dev;
          }

        printf("adc_main: Interrupted read...\n");
      }
    else if (nbytes == 0)
      {
        printf("adc_main: No data read, Ignoring\n");
      }

    /* Print the sample data on successful return */

    else
      {
        int nsamples = nbytes / sizeof(struct adc_msg_s);
        if (nsamples * sizeof(struct adc_msg_s) != nbytes)
          {
            printf("adc_main: read size=%ld is not a multiple of sample size=%d, Ignoring\n",
                   (long)nbytes, sizeof(struct adc_msg_s));
          }
        else
          {
            printf("Sample:\n");
            for (i = 0; i < nsamples; i++)
              {
                printf("%d: channel: %d value: %d\n",
                       i+1, sample[i].am_channel, sample[i].am_data);
              }
          }
      }
  }

  close(fd);
  return OK;

  /* Error exits */

errout_with_dev:
  close(fd);

errout:
  printf("Terminating!\n");
  fflush(stdout);
  return errval;
}

