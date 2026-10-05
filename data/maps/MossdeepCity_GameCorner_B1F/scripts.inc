MossdeepCity_GameCorner_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_CUSTOM_PlayerHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_CUSTOM_PlayerHouse_2F_OnWarp
	.byte 0

MossdeepCity_CUSTOM_PlayerHouse_2F_OnTransition:
	setflag FLAG_SYS_B_DASH
	call_if_lt VAR_LITTLEROOT_RIVAL_STATE, 2, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckSetReadyToMeetBrendan
	call_if_ge VAR_LITTLEROOT_RIVAL_STATE, 3, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckShouldUpdateBrendanPos
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 4, PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckShouldUpdateBrendanPos::
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_TryUpdateBrendanPos
	goto_if_ge VAR_BIRCH_LAB_STATE, 2, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_Ret
	goto MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_TryUpdateBrendanPos

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_TryUpdateBrendanPos::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_Ret
	@ Odd that the MaysHouse equivalent was used below instead
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_MaysHouse_2F_EventScript_Ret
	setobjectxyperm LOCALID_RIVALS_HOUSE_2F_RIVAL, 0, 2
	setobjectmovementtype LOCALID_RIVALS_HOUSE_2F_RIVAL, MOVEMENT_TYPE_FACE_UP
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_Ret::
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckSetReadyToMeetBrendan::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_SetReadyToMeetBrendan
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_SetReadyToMeetBrendan::
	setvar VAR_LITTLEROOT_RIVAL_STATE, 2
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_OnWarp:
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckInitDecor
	.2byte 0

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckInitDecor::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SecretBase_EventScript_InitDecorations
	end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_RivalsPokeBall::
	lockall
	goto_if_eq VAR_LITTLEROOT_RIVAL_STATE, 2, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendan
	msgbox RivalsHouse_2F_Text_ItsRivalsPokeBall, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendan::
	delay 10
	addobject LOCALID_RIVALS_HOUSE_2F_RIVAL
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanEnters
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 10
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanNorth
	call_if_eq VAR_FACING, DIR_SOUTH, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanSouth
	call_if_eq VAR_FACING, DIR_WEST, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanWest
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanEast
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanNorth::
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerNorth
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_PlayerWatchBrendanNorth
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCNorth
	waitmovement 0
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanSouth::
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerSouth
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_PlayerWatchBrendanSouth
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCSouth
	waitmovement 0
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanWest::
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerWest
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_PlayerWatchBrendanWest
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCWest
	waitmovement 0
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_MeetBrendanEast::
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerEast
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVALS_HOUSE_2F_RIVAL, MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCEast
	waitmovement 0
	return

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanEnters:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCNorth:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_PlayerWatchBrendanNorth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerSouth:
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCSouth:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_PlayerWatchBrendanSouth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerWest:
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCWest:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_PlayerWatchBrendanWest:
	delay_8
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanApproachPlayerEast:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_BrendanWalkToPCEast:
	walk_up
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

@ Unused, the player is already facing this direction so its unneeded
MossdeepCity_CUSTOM_PlayerHouse_2F_Movement_PlayerWatchBrendanEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_PC::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckPlayersPC
	goto_if_eq VAR_RESULT, FEMALE, MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckRivalsPC
	end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckPlayersPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	releaseall
	end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_TurnOffPlayerPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

MossdeepCity_CUSTOM_PlayerHouse_2F_EventScript_CheckRivalsPC::
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

CUSTOM_PlayersHouse_2F_EventScript_Notebook::
	msgbox PlayersHouse_2F_Text_Notebook, MSGBOX_SIGN
	end

CUSTOM_PlayersHouse_2F_EventScript_GameCube::
	msgbox PlayersHouse_2F_Text_ItsAGameCube, MSGBOX_SIGN
	end

CUSTOM_PlayersHouse_2F_Text_ClockIsStopped:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

CUSTOM_PlayersHouse_2F_Text_HowDoYouLikeYourRoom:
	.string "MOM: {PLAYER}, how do you like your\n"
	.string "new room?\p"
	.string "Good! Everything's put away neatly!\p"
	.string "They finished moving everything in\n"
	.string "downstairs, too.\p"
	.string "POKéMON movers are so convenient!\p"
	.string "Oh, you should make sure that\n"
	.string "everything's all there on your desk.$"

CUSTOM_PlayersHouse_2F_Text_Notebook:
	.string "{PLAYER} flipped open the notebook.\p"
	.string "ADVENTURE RULE NO. 1\n"
	.string "Open the MENU with START.\p"
	.string "ADVENTURE RULE NO. 2\n"
	.string "Record your progress with SAVE.\p"
	.string "The remaining pages are blank…$"

CUSTOM_PlayersHouse_2F_Text_ItsAGameCube:
	.string "It's a Nintendo GameCube.\p"
	.string "A Game Boy Advance is connected to\n"
	.string "serve as the Controller.$"

