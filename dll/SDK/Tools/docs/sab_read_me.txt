//Lightsaber configurations, use by name

NOTE: add new sabers by putting their entries in a .sab file in ext_data/sabers

defaults and explanations of fields:

	//saber type
	saberType				SABER_NONE - what kind of saber to use ( SABER_SINGLE, SABER_STAFF)

	//saber hilt
	saberModel				"models/weapons2/saber_reborn/saber_w.glm" - what saber hilt model to use
	
	A note about saber hilt models:  the surface names on saber models should *always* start with "w_", the code expects it.

	customSkin				"" - a .skin file to apply to the saber hilt model, if any (overrides saber hilt model's internal texture mapping)

	soundOn					"sound/weapons/saber/enemy_saber_on.wav" - turn on sound
	soundLoop				"sound/weapons/saber/saberhum3.wav" - loop sound (must be a .wav file)
	soundOff				"sound/weapons/saber/enemy_saber_off.wav" - turn off sound

	//blades
	numBlades				1 - how many blades it has (min of 1, max of 8)

	A note about blade tags:  each blade will be drawn from it's corresponding tag's position and in the direction (negative X axis in ModView) of that tag.
	The naming of the tags must be as follows:
	"tag_blade1" for the first blade.  I made the code fall back to "tag_flash" if it can't find the tag_blades so that the code will still work pre-JKA sabers, but we you should always use the new name.
	All following blades (if applicable) should be "tag_blade2", "tag_blade3", etc., to a maximum of 8 blades ("tag_blade8")

	//saber length
	//NOTE: these should be inputted in order - setting "saberLength" automatically sets all of the others to the same length
	saberLength				32 - how long the saber's first blade should be (minimum of 4)
	saberLength2			saberLength - how long the saber's second blade should be (minimum of 4)
	saberLength3			saberLength - how long the saber's third blade should be (minimum of 4)
	saberLength4			saberLength - how long the saber's fourth blade should be (minimum of 4)
	saberLength5			saberLength - how long the saber's fifth blade should be (minimum of 4)
	saberLength6			saberLength - how long the saber's sixth blade should be (minimum of 4)
	saberLength7			saberLength - how long the saber's seventh blade should be (minimum of 4)
	saberLength8			saberLength - how long the saber's eigth blade should be (minimum of 4)

	//saber radius
	//NOTE: these should be inputted in order - setting "saberLength" automatically sets all of the others to the same length
	saberRadius				3 - how wide the saber's first blade should be (minimum of 0.25)
	saberRadius2			saberRadius - how wide the saber's second blade should be (minimum of 0.25)
	saberRadius3			saberRadius - how wide the saber's third blade should be (minimum of 0.25)
	saberRadius4			saberRadius - how wide the saber's fourth blade should be (minimum of 0.25)
	saberRadius5			saberRadius - how wide the saber's fifth blade should be (minimum of 0.25)
	saberRadius6			saberRadius - how wide the saber's sixth blade should be (minimum of 0.25)
	saberRadius7			saberRadius - how wide the saber's seventh blade should be (minimum of 0.25)
	saberRadius8			saberRadius - how wide the saber's eigth blade should be (minimum of 0.25)

	//saberColor - valid colors:  random, red, orange, yellow, green, blue, and purple
	//NOTE: these should be inputted in order - setting "saberColor" automatically sets all of the others to the same color
	saberColor				red - what color the saber's 1st blade should be
	saberColor2				saberColor - what color the saber's 2nd blade should be
	saberColor3				saberColor - what color the saber's 3rd blade should be
	saberColor4				saberColor - what color the saber's 4th blade should be
	saberColor5				saberColor - what color the saber's 5th blade should be
	saberColor6				saberColor - what color the saber's 6th blade should be
	saberColor7				saberColor - what color the saber's 7th blade should be
	saberColor8				saberColor - what color the saber's 8th blade should be

	//locked style
	saberStyle				none - what one style it's limited to, if any (fast, medium, strong, desann, tavion, dual, staff)
	
	//NOTE: the "saberStyle" field stomps these next two - don't use them together, use the above one if you only want to allow ONE style (that style is given to the person using that saber)
	saberStyleLearned			none - what styles they should get when they are given this saber (they don't have to use these, but they become available if they didn't know them before)
	saberStyleForbidden			none - what styles *cannot* be used with this saber (it doesn't take the style from them, it just doesn't allow them to use these styles if they try)

	//maxChain
	maxChain				0 - how many moves can be chained in a row with this weapon (-1 is infinite, 0 is use default behavior)

	//lockable
	lockable				1 - whether or not it can be stuck in a saber lock

	//throwable
	throwable				1 - whether or not it can be thrown

	//disarmable
	disarmable				1 - whether or not it can be disarmed (dropped)
 
	//blocking
	blocking				1 - whether or not user will try to block incoming shots (shots always bounce off it, this just determines if the user *tries* to block with it)
 
	//twoHanded
	twoHanded				0 - whether or not it requires 2 hands (makes it restrict force powers but makes it stronger in locks or parries)

	//force power restrictions
	forceRestrict			0 - what force powers it restricts, use these keys, a seperate entry per power:
							FP_HEAL					
							FP_LEVITATION			
							FP_SPEED				
							FP_PUSH					
							FP_PULL					
							FP_TELEPATHY			
							FP_GRIP					
							FP_LIGHTNING
							FP_SABERTHROW
							FP_SABER_DEFENSE
							FP_SABER_OFFENSE
							//new Jedi Academy powers
							FP_RAGE
							FP_PROTECT
							FP_ABSORB
							FP_DRAIN
							FP_SEE

	//lockBonus
	lockBonus				0 - this pushes harder/weaker in saberlocks

	//parryBonus
	parryBonus				0 - this is stronger/weaker in a parry (harder to break, more likely to knockaway)

	//breakParryBonus
	breakParryBonus			0 - this is more/less likely to break a parry
	breakParryBonus2		0 - for second blade style (see bladeStyle2Start below)

	//disarmBonus
	disarmBonus			0 - this is more/less likely to disarm another saber in a saberlock or knockaway
	disarmBonus2			0 - for second blade style (see bladeStyle2Start below)

	singleBladeStyle		none - makes it so that you use a different style if you only have the first blade active

	singleBladeThrowable	0 - makes it so that you can throw this saber if only the first blade is on

	brokenSaber1			none - if saber is actually hit by another saber, it can be cut in half/broken and will be replaced with this saber in your right hand
	brokenSaber2			none - if saber is actually hit by another saber, it can be cut in half/broken and will be replaced with this saber in your left hand

	returnDamage			0 - when returning from a saber throw, it keeps spinning and doing damage

//===The following fields were added after retail version:===========================================================================
	//these values are global to the saber, like all of the ones above

	//done in cgame (client-side code)
	spinSound				none - if set, plays this sound as it spins when thrown
	swingSound1 - swingSound3		none - if set, plays one of these 3 sounds when swung during an attack - NOTE: must provide all 3!!!
	fallSound1 - fallSound3			none - if set, plays one of these 3 sounds when weapon falls to the ground - NOTE: must provide all 3!!!
	onInWater				0 - if set, weapon stays active even in water

	//done in game (server-side code)
	bounceOnWalls			0 - if non-zero, the saber will bounce back when it hits solid architecture (good for real-sword type mods)
	moveSpeedScale			1.0 - you move faster/slower when using this saber
	animSpeedScale			1.0 - plays normal attack animations faster/slower
	boltToWrist				0 - if set, saber model is bolted to wrist, not in hand... useful for things like claws & shields, etc.

	//replace certain anims
	readyAnim				none - anim to use when standing idle (use name of enum in anims.h or BehavEd's list)
	drawAnim				none - anim to use when drawing weapon (use name of enum in anims.h or BehavEd's list)
	putawayAnim				none - anim to use when putting weapon away (use name of enum in anims.h or BehavEd's list)
	tauntAnim				none - anim to use when hit "taunt" (use name of enum in anims.h or BehavEd's list)
	bowAnim					none - anim to use when hit "bow" (use name of enum in anims.h or BehavEd's list)
	meditateAnim				none - anim to use when hit "meditate" (use name of enum in anims.h or BehavEd's list)
	flourishAnim				none - anim to use when hit "flourish" (use name of enum in anims.h or BehavEd's list)
	gloatAnim				none - anim to use when hit "gloat" (use name of enum in anims.h or BehavEd's list)

	//optionally disallow certain types of moves and attacks
	noRollStab				0 - if set, cannot do roll-stab move at end of roll
	noPullAttack			0 - if set, cannot do pull+attack move (move not available in MP anyway)
	noBackAttack			0 - if set, cannot do back-stab moves
	noStabDown				0 - if set, cannot do stabdown move (when enemy is on ground)
	noWallRuns				0 - if set, cannot side-run or forward-run on walls
	noWallFlips				0 - if set, cannot do backflip off wall or side-flips off walls
	noWallGrab				0 - if set, cannot grab wall & jump off
	noRolls					0 - if set, cannot roll
	noFlips					0 - if set, cannot do flips
	noCartwheels			0 - if set, cannot do cartwheels
	noKicks					0 - if set, cannot do kicks (can't do kicks anyway if using a throwable saber/sword)
	noMirrorAttacks			0 - if set, cannot do the simultaneous attack left/right moves (only available in Dual Lightsaber Combat Style)
	
	//done in both cgame and game (BG code)
	kataMove				0 - if set, player will execute this move when they press both attack buttons at the same time (see list below for valid values)
	lungeAtkMove			0 - if set, player will execute this move when they crouch+fwd+attack (see list below for valid values)
	jumpAtkUpMove			0 - if set, player will execute this move when they jump+attack (see list below for valid values)
	jumpAtkFwdMove			0 - if set, player will execute this move when they jump+fwd+attack (see list below for valid values)
	jumpAtkBackMove			0 - if set, player will execute this move when they jump+back+attack (see list below for valid values)
	jumpAtkRightMove		0 - if set, player will execute this move when they jump+rightattack (see list below for valid values)
	jumpAtkLeftMove			0 - if set, player will execute this move when they jump+left+attack (see list below for valid values)
	//NOTE: these "move" fields refer to saber moves that are defined in code.  Set to LS_NONE to have the normal move removed, set to one of the following values to override the current move
							LS_NONE	- Do a regular attack instead of a special move (overrides the usual special move with a normal attack)
							// Attacks
							LS_A_TL2BR
							LS_A_L2R
							LS_A_BL2TR
							LS_A_BR2TL
							LS_A_R2L
							LS_A_TR2BL
							LS_A_T2B
							LS_A_BACKSTAB
							LS_A_BACK
							LS_A_BACK_CR
							LS_ROLL_STAB
							LS_A_LUNGE
							LS_A_JUMP_T__B_
							LS_A_FLIP_STAB
							LS_A_FLIP_SLASH
							LS_JUMPATTACK_DUAL
							LS_JUMPATTACK_ARIAL_LEFT
							LS_JUMPATTACK_ARIAL_RIGHT
							LS_JUMPATTACK_CART_LEFT
							LS_JUMPATTACK_CART_RIGHT
							LS_JUMPATTACK_STAFF_LEFT
							LS_JUMPATTACK_STAFF_RIGHT
							LS_BUTTERFLY_LEFT
							LS_BUTTERFLY_RIGHT
							LS_A_BACKFLIP_ATK
							LS_SPINATTACK_DUAL
							LS_SPINATTACK
							LS_LEAP_ATTACK
							LS_SWOOP_ATTACK_RIGHT
							LS_SWOOP_ATTACK_LEFT
							LS_TAUNTAUN_ATTACK_RIGHT
							LS_TAUNTAUN_ATTACK_LEFT
							LS_KICK_F
							LS_KICK_B
							LS_KICK_R
							LS_KICK_L
							LS_KICK_S
							LS_KICK_BF
							LS_KICK_RL
							LS_KICK_F_AIR
							LS_KICK_B_AIR
							LS_KICK_R_AIR
							LS_KICK_L_AIR
							LS_STABDOWN
							LS_STABDOWN_STAFF
							LS_STABDOWN_DUAL
							LS_DUAL_SPIN_PROTECT
							LS_STAFF_SOULCAL
							LS_A1_SPECIAL
							LS_A2_SPECIAL
							LS_A3_SPECIAL
							LS_UPSIDE_DOWN_ATTACK
							LS_PULL_ATTACK_STAB
							LS_PULL_ATTACK_SWING
							LS_SPINATTACK_ALORA
							LS_DUAL_FB
							LS_DUAL_LR
							LS_HILT_BASH

	//***these values can be specified differently for different blades (see "bladeStyle2Start" below for more info)***

	//done in cgame (client-side code)
	noWallMarks				0 - if 1, stops the saber from drawing marks on the world (good for real-sword type mods)
	noDlight				0 - if 1, stops the saber from drawing a dynamic light (good for real-sword type mods)
	noBlade					0 - if 1, stops the saber from drawing a blade (good for real-sword type mods)
	noClashFlare				0 - if non-zero, the saber will not do the big, white clash flare with other sabers
	trailStyle				0 - default (0) is normal, 1 is a motion blur and 2 is no trail at all (good for real-sword type mods)
	g2MarksShader				none - if set, the game will use this shader for marks on enemies instead of the default "gfx/damage/saberglowmark"
	hitSound1 - hitSound3			none - if set, plays one of these 3 sounds when saber hits a person - NOTE: must provide all 3!!!
	blockSound1 - blockSound3		none - if set, plays one of these 3 sounds when saber/sword hits another saber/sword - NOTE: must provide all 3!!!
	bounceSound1 - bounceSound3		none - if set, plays one of these 3 sounds when saber/sword hits a wall and bounces off (must set bounceOnWall to 1 to use these sounds) - NOTE: must provide all 3!!!
	blockEffect				none - if set, plays this effect when the saber/sword hits another saber/sword (instead of "saber/saber_block.efx")
	hitPersonEffect				none - if set, plays this effect when the saber/sword hits a person (instead of "saber/blood_sparks_mp.efx" in MP and "sparks/blood_sparks2" in SP)
	hitOtherEffect				none - if set, plays this effect when the saber/sword hits something else damagable (instead of "saber/saber_cut.efx")

	//done in game (server-side code)
	knockbackScale				0 - if non-zero, uses damage done to calculate an appropriate amount of knockback
	damageScale				1 - scale up or down the damage done by the saber
	noDismemberment				0 - if non-zero, the saber never does dismemberment (good for pointed/blunt melee weapons)
	noIdleEffect				0 - if non-zero, the saber will not do damage or any effects when it is idle (not in an attack anim).  (good for real-sword type mods)
	splashRadius				0 - radius of splashDamage
	splashDamage				0 - amount of splashDamage, 100% at a distance of 0, 0% at a distance = splashRadius
	splashKnockback				0 - amount of splashKnockback, 100% at a distance of 0, 0% at a distance = splashRadius
	alwaysBlock				0 - if set, the blades will always be blocking (good for things like shields that should always block)
	noManualDeactivate			0 - if set, the blades cannot manually be toggled on and off (does not affect turning the whole saber on/off, just hitting the saber style cycle button when using dual sabers or a multi-blade saber)

	//***The following can be different for the extra blades - not setting them individually defaults them to the value for the whole saber (and first blade)***
	//***NOTE: you can only have a maximum of 2 "styles" of blades, so this next value, "bladeStyle2Start" is the number of the first blade to use these value on... all blades before this use the normal values above, all blades at and after this number use the secondary values below***
	bladeStyle2Start			0 - if set, blades from this number and higher use the following values (otherwise, they use the normal values already set)

	//done in cgame (client-side code)
	noWallMarks2				0 - if 1, stops the saber from drawing marks on the world (good for real-sword type mods)
	noDlight2				0 - if 1, stops the saber from drawing a dynamic light (good for real-sword type mods)
	noBlade2				0 - if 1, stops the saber from drawing a blade (good for real-sword type mods)
	noClashFlare2				0 - if non-zero, the saber will not do the big, white clash flare with other sabers
	trailStyle2				0 - default (0) is normal, 1 is a motion blur and 2 is no trail at all (good for real-sword type mods)
	g2MarksShader2				none - if set, the game will use this shader for marks on enemies instead of the default "gfx/damage/saberglowmark"
	hit2Sound1 - hit2Sound3			none - if set, plays one of these 3 sounds when saber hits a person - NOTE: must provide all 3!!!
	block2Sound1 - block2Sound3		none - if set, plays one of these 3 sounds when saber/sword hits another saber/sword - NOTE: must provide all 3!!!
	bounce2Sound1 - bounce2Sound3		none - if set, plays one of these 3 sounds when saber/sword hits a wall and bounces off (must set bounceOnWall to 1 to use these sounds) - NOTE: must provide all 3!!!
	blockEffect2				none - if set, plays this effect when the saber/sword hits another saber/sword (instead of "saber/saber_block.efx")
	hitPersonEffect2			none - if set, plays this effect when the saber/sword hits a person (instead of "saber/blood_sparks_mp.efx" in MP and "sparks/blood_sparks2" in SP)
	hitOtherEffect2				none - if set, plays this effect when the saber/sword hits something else damagable (instead of "saber/saber_cut.efx")

	//done in game (server-side code)
	knockbackScale2				0 - if non-zero, uses damage done to calculate an appropriate amount of knockback
	damageScale2				1 - scale up or down the damage done by the saber
	noDismemberment2			0 - if non-zero, the saber never does dismemberment (good for pointed/blunt melee weapons)
	noIdleEffect2				0 - if non-zero, the saber will not do damage or any effects when it is idle (not in an attack anim).  (good for real-sword type mods)
	splashRadius2				0 - radius of splashDamage
	splashDamage2				0 - amount of splashDamage, 100% at a distance of 0, 0% at a distance = splashRadius
	splashKnockback2			0 - amount of splashKnockback, 100% at a distance of 0, 0% at a distance = splashRadius
	alwaysBlock2				0 - if set, the blades will always be blocking (good for things like shields that should always block)
	noManualDeactivate2			0 - if set, the blades cannot manually be toggled on and off (does not affect turning the whole saber on/off, just hitting the saber style cycle button when using dual sabers or a multi-blade saber)
//=========================================================================================================================================
