# I Can Count
Well, actually, I can't. You'd be surprised how hard it is to count to three 10 times over a 30 minute period of a heavy lifting workout. The Pebble app runs on the watch and provides a simple stopwatch and counter. I threw it together one afternoon before I went to the gym, so, it's not perfect.

# TODO
 - Remember state between app restarts.
 - Save a lot of battery: Originally it showed tenths in the stopwatch but after I used the app a couple times I realized it was unnecessary for this use case, so it should use Pebble's built-in clock callbacks every second rather than updating on a timer.
 - Show the last split time and restart the large stopwatch after a split action. This way you can see how much time you have spent total, but also easily tell how long it has been since your last rep. Typically when lifting you try to hit your sets at a constant interval. You might wait 1 minute, or 3 minutes between sets, depending on your necessary recovery time.
 - All the things to make it publishable in the app store.