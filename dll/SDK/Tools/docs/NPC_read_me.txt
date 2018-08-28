//Star Wars
/*
NOTE: add new NPCs by putting their entries in a .npc file in ext_data

defaults and explanations of fields:
	aggression			3		How likely they are to attack (from 1 (least) to 5 (most))
	aim				3		How good their aim is (from 1 (worst) to 5 (best))
	earshot				1024		How far in map units they can hear, in map units
	evasion				3		How likely they are to take cover or defensive maneuvers (from 1 (least) to 5 (most))
	hfov				45		Horizontal field of view, in angles
	intelligence			3		How smart they are, in general (from 1 (least) to 5 (most))
	move				3		How complex their moves are when evading or in combat  (from 1 (least) to 5 (most))
	reactions			3		How quickly they react  (from 1 (worst) to 5 (best))
	shootDistance			0		Overrides current weapon's max range
	vfov				34		Vertical field of view, in angles
	vigilance			0.1		How likely they are to notice something (from 0 (never) to 1 (always))
	visrange			2048		How far away they can see something, in map units
	race				none		human, borg, parasite, klingon, malon, hirogen, stasis, species8472, dreadnought, harvester, reaver, avatar, vulcan		
	playerTeam			none		player, enemy, neutral
	enemyTeam			none		player, enemy, neutral

	health				100		Health of entity (if not supplied by designer) 

	moveType			"runjump"	Which movetype they can be (other choices are "static", "walk" and "flyswim"
	yawSpeed			50		How quickly they can turn
	walkSpeed			150		How fast they walk
	runSpeed			300		How fast they run
	acceleration			15		Acceleration (accel x 20fps = speed up per second, so accel of 15 means they can go from 0 to 300 in one second)
								Accel of 0 means don't accel/decel - just start/stop (good if you're a slow mover anyway and/or robotic - like a Borg)

	scaleX				100		X (horiz) scale, 100 is normal 100% scale
	scaleY				100		Y (horiz) scale, 100 is normal 100% scale
	scaleZ				100		Z (vert) scale, 100 is normal 100% scale
	scale				100		Sets all above 3 to what you specify
	headModel			"hazard"	model directory/skin name
	torsoModel			"hazard"	model directory/skin name
	legsModel			"hazard"	model directory/skin name
	headYawRangeLeft		70		How far left you can turn your head (angles)
	headYawRangeRight		70		How far right you can turn your head (angles)
	headPitchRangeUp		60		How far up you can tilt your head (angles)
	headPitchRangeDown		60		How far down you can tilt your head (angles)
	torsoYawRangeLeft		60		How far left you can turn your torso (angles)
	torsoYawRangeRight		60		How far right you can turn your torso (angles)
	torsoPitchRangeUp		30		How far up you can tilt your torso (angles)
	torsoPitchRangeDown		70		How far down you can tilt your torso (angles)

	snd				"munro"		subdirectory of sound/player from which to get custom sounds (pain, death, jump, etc.)
	dismemberProbHead		0	probability of head being dismembered ( from 0 (never) to 100 (always) )
	dismemberProbArms		0	probability of arms being dismembered ( from 0 (never) to 100 (always) )
	dismemberProbHands		0	probability of hands being dismembered ( from 0 (never) to 100 (always) )
	dismemberProbLegs		0	probability of legs being dismembered ( from 0 (never) to 100 (always) )
	dismemberProbWaist		0	probability of waist being dismembered ( from 0 (never) to 100 (always) )

	//starting weapon
	weapon					WP_NONE - what weapon to start with:
							WP_SABER
							WP_BRYAR_PISTOL
							WP_BLASTER
							WP_DISRUPTOR
							WP_BOWCASTER
							WP_REPEATER
							WP_DEMP2
							WP_FLECHETTE
							WP_ROCKET_LAUNCHER
							WP_THERMAL
							WP_TRIP_MINE
							WP_DET_PACK
							WP_STUN_BATON
							WP_MELEE
							WP_EMPLACED_GUN
							WP_BOT_LASER
							WP_TURRET
							WP_ATST_MAIN
							WP_ATST_SIDE
							WP_TIE_FIGHTER
							WP_RAPID_FIRE_CONC
							WP_BLASTER_PISTOL

	altFire					0	- whether or not to use the alt-fire mode of your weapon as the default mode (0 = no, 1 = yes)			

	//FIXME: have a sabers.cfg and just name your saber here
	//saber type
	saber					"" - what kind of saber to use (from sabers.cfg)
	saber2				"" - what kind of saber to use as a second saber (from sabers.cfg)

	//saber length
	//NOTE: these should be inputted in order - setting "saberLength" automatically sets all of the others to the same length
	saberLength				32 - how long the 1st saber's first blade should be (minimum of 4)
	saberLength2			saberLength - how long the 1st saber's second blade should be (minimum of 4)
	saberLength3			saberLength - how long the 1st saber's third blade should be (minimum of 4)
	saberLength4			saberLength - how long the 1st saber's fourth blade should be (minimum of 4)
	saberLength5			saberLength - how long the 1st saber's fifth blade should be (minimum of 4)
	saberLength6			saberLength - how long the 1st saber's sixth blade should be (minimum of 4)
	saberLength7			saberLength - how long the 1st saber's seventh blade should be (minimum of 4)
	saberLength8			saberLength - how long the 1st saber's eigth blade should be (minimum of 4)
	saber2Length			32 - how long the 2nd saber's first blade should be (minimum of 4)
	saber2Length2			saberLength - how long the 2nd saber's second blade should be (minimum of 4)
	saber2Length3			saberLength - how long the 2nd saber's third blade should be (minimum of 4)
	saber2Length4			saberLength - how long the 2nd saber's fourth blade should be (minimum of 4)
	saber2Length5			saberLength - how long the 2nd saber's fifth blade should be (minimum of 4)
	saber2Length6			saberLength - how long the 2nd saber's sixth blade should be (minimum of 4)
	saber2Length7			saberLength - how long the 2nd saber's seventh blade should be (minimum of 4)
	saber2Length8			saberLength - how long the 2nd saber's eigth blade should be (minimum of 4)

	//saber radius
	//NOTE: these should be inputted in order - setting "saberLength" automatically sets all of the others to the same length
	saberRadius				3 - how wide the 1st saber's first blade should be (minimum of 0.25)
	saberRadius2			saberRadius - how wide the 1st saber's second blade should be (minimum of 0.25)
	saberRadius3			saberRadius - how wide the 1st saber's third blade should be (minimum of 0.25)
	saberRadius4			saberRadius - how wide the 1st saber's fourth blade should be (minimum of 0.25)
	saberRadius5			saberRadius - how wide the 1st saber's fifth blade should be (minimum of 0.25)
	saberRadius6			saberRadius - how wide the 1st saber's sixth blade should be (minimum of 0.25)
	saberRadius7			saberRadius - how wide the 1st saber's seventh blade should be (minimum of 0.25)
	saberRadius8			saberRadius - how wide the 1st saber's eigth blade should be (minimum of 0.25)
	saber2Radius			3 - how wide the 2nd saber's first blade should be (minimum of 0.25)
	saber2Radius2			saber2Radius - how wide the 2nd saber's second blade should be (minimum of 0.25)
	saber2Radius3			saber2Radius - how wide the 2nd saber's third blade should be (minimum of 0.25)
	saber2Radius4			saber2Radius - how wide the 2nd saber's fourth blade should be (minimum of 0.25)
	saber2Radius5			saber2Radius - how wide the 2nd saber's fifth blade should be (minimum of 0.25)
	saber2Radius6			saber2Radius - how wide the 2nd saber's sixth blade should be (minimum of 0.25)
	saber2Radius7			saber2Radius - how wide the 2nd saber's seventh blade should be (minimum of 0.25)
	saber2Radius8			saber2Radius - how wide the 2nd saber's eigth blade should be (minimum of 0.25)

	//saberColor - valid colors:  random, red, orange, yellow, green, blue, and purple
	//NOTE: these should be inputted in order - setting "saberColor" automatically sets all of the others to the same color
	saberColor				red - what color the 1st saber's 1st blade should be
	saberColor2				saberColor - what color the 1st saber's 2nd blade should be
	saberColor3				saberColor - what color the 1st saber's 3rd blade should be
	saberColor4				saberColor - what color the 1st saber's 4th blade should be
	saberColor5				saberColor - what color the 1st saber's 5th blade should be
	saberColor6				saberColor - what color the 1st saber's 6th blade should be
	saberColor7				saberColor - what color the 1st saber's 7th blade should be
	saberColor8				saberColor - what color the 1st saber's 8th blade should be
	saber2Color				red - what color the 2nd saber's 1st blade should be
	saber2Color2			saberColor - what color the 2nd saber's 2nd blade should be
	saber2Color3			saberColor - what color the 2nd saber's 3rd blade should be
	saber2Color4			saberColor - what color the 2nd saber's 4th blade should be
	saber2Color5			saberColor - what color the 2nd saber's 5th blade should be
	saber2Color6			saberColor - what color the 2nd saber's 6th blade should be
	saber2Color7			saberColor - what color the 2nd saber's 7th blade should be
	saber2Color8			saberColor - what color the 2nd saber's 8th blade should be

	//starting saber style
	saberStyle				0 - which style to start with (0-7)

	//force powers
	forcePowerMax			100 - maximum force power
	forceRegenRate			100 - milliseconds between force regens (interval) - min is 50
	forceRegenAmount		1 - force regeneration rate (points per interval)

	FP_HEAL					0 - force heal level (0-5)
	FP_LEVITATION			0 - force jump level (0-5)
	FP_SPEED				0 - force speed level (0-5)
	FP_PUSH					0 - force push level (0-5)
	FP_PULL					0 - force pull level (0-5)
	FP_TELEPATHY			0 - mind trick level (0-5)
	FP_GRIP					0 - force grip level (0-5)
	FP_LIGHTNING			0 - force lightning level (0-5)
	FP_SABERTHROW			0 - saber throw level (0-5)
	FP_SABER_DEFENSE		0 - saber defense level (0-5)
	FP_SABER_OFFENSE		0 - saber offense level (0-5)
	//new Jedi Academy powers
	FP_RAGE					0 - speed, invincibility and extra damage for short period, drains your health and leaves you weak and slow afterwards.
	FP_PROTECT				0 - protect against physical/energy (level 1 stops blaster/energy bolts, level 2 stops projectiles, level 3 protects against explosions)
	FP_ABSORB				0 - protect against dark force powers (grip, lightning, drain)
	FP_DRAIN				0 - drain force power for health
	FP_SEE					0 - detect/see hidden enemies

*/

