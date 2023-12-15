Disclaimer: most of this data is garbage. I saved the individual files based on each test with different wait values, but the csv values didn't seem to save some of the values we need so I had to sort of guesstimate based on the values that were saved and this is the second time we've run through the lab collecting values. CSV files for each variation will be added to repo. We were able to notice the intended changes with different values, we just failed to properly save the data. 

Section 1:
Formula for drift:
        drift (s) = Measured - Ideal
        Measured(time lapse) = (# oscillations / hour) * Tmean

-Jitter: Deviation from an ideal signal whether its slower of faster on the edge crossings.


-sleep.c
	-no additional delay added:
			ideal:		measured:
	Period:		3 ms		2.94 ms
	Frequency:	500 Hz		456.1 Hz	


	-1000µs delay added(using k_busy_wait):
			ideal:		measured:
	Period:		4.5 ms		4.65 ms
	Frequency:	220 Hz	    215 Hz


	-1500µs delay added(using k_busy_wait):
			ideal:		measured:
	Period:		7.00 ms		7.1 ms
	Frequency:	140 Hz	133 Hz
    



-kernel.c
	-no additional delay added:
			ideal:		measured:
	Period:		2 ms		1.996 ms
	Frequency:	500 Hz		501 Hz

	-1000µs delay added(using k_busy_wait before timer start):
			ideal:		measured:
	Period:		3 ms		3.36 ms
	Frequency:	300 Hz	328 Hz

	-1500µs delay added(using k_busy_wait before timeer start):
			ideal:		measured:
	Period:		3 ms		2.86 ms
	Frequency:	400 Hz	    386 Hz

	-2000µs delay added(using k_busy_wait after timer start):
			measured:
	Period:		6.9 ms	
	Frequency:	157 Hz



-rtc.c (realtime clock)
	- couldn't get realtime clock to compile for some reason

-busy.c
	-1000µs delay used:
			ideal:		measured:
	Period:		2 ms		1.61 ms
	Frequency:	500 Hz		498 Hz


	-1500µs delay used:
			ideal:		measured:
	Period:		2 ms	1.99 ms
	Frequency:	500 Hz	481 Hz

	
	-2500µs delay used:
			ideal:		measured:
	Period:		2 ms		2.46 ms
	Frequency:	500 Hz	420 Hz

Section 2:
-gpio_interrupt.c
	-Using signal generator to drive the board using Pin A1 with measure from pin A0
	-Unmodified code:
		-Delay between sync signal(500Hz) and output from board:
			Delay: -7.9 µs
	-Increase delay in code using busy_wait loop before toggle
		-k_busy_wait(300) increase by 300µs for toggle delay
			-Delay: +292µs


Section 3:
-gpio_interrupt.c
	-Adding message queue to send message with toggle
		-Delay between sync signal(500 Hz)
			-Delay: -25 µs
	-Increaese delay in code using busy_wait loop before toggle
		-k_busy_wait(300) increase by 300µs for toggle delay
			-Delay: -318 µs