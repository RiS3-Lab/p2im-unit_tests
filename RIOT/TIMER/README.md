We use one firmware to test two functional operations: execute callback after interrupt and read counter value

RIOT only supports channel 0 of time 0 for NXP MK64FN1M0VLL12 MCU, so you have to make the following changes to `main.c` for NXP MK64FN1M0VLL12 MCU. 

```diff
diff --git a/RIOT/TIMER/main.c b/RIOT/TIMER/main.c
index d517d41..30b3c69 100644
--- a/RIOT/TIMER/main.c
+++ b/RIOT/TIMER/main.c
@@ -53,7 +53,7 @@ int main(void)
     timer_init(TIMER_DEV(0),1000,time,&a); // 1000 is the number of ticks per second, "time" is the callback and "a" is an optional parameter passed to callback
     
     timer_read(TIMER_DEV(0)); // reads count register of timer, does not affect fucntionality  is only a read of current count 
-    timer_set(TIMER_DEV(0),1,100); //set a timeout in ticks (100 ticks)  for channel 1 of timer(0), which calls "time" callback defined in timer_init when timeout ticks have passed 
+    timer_set(TIMER_DEV(0),0,100); //set a timeout in ticks (100 ticks)  for channel 0 of timer(0), which calls "time" callback defined in timer_init when timeout ticks have passed 
     timer_stop(TIMER_DEV(0));  // stop the timer
     timer_start(TIMER_DEV(0)); // start de timer this is unnecessary (part of timer_init) unless stop was called previously
```