# EscapeTheRoom

EscapeTheRoom is a hello world project I worked on to introduce me into the world of Unreal. It uses hard coded C++, interacting with Unreal's Visual Coding system, Blueprint.

# To Run: 

  - Download. 

  - Open the BuildingEscape Unreal Engine Project File in Unreal Engine Version 4.20.

  - When it asks to build the missing modules click 'Yes'

  - Then click play to quick test or launch to play. 

  - There is no win condition so when you fall out of the second door that's the end.  


# Objective: 

     Using visual clues escape the staring room.
     
# Key points:

  - Under ...BuildingEscape/Source/BuildingEscape is all my C++ Work.

  - Grabber is attached to the pawn blueprint to allow the player to grab objects with right click using ray casting.

  - OpenDoor Determines if the conditions have been met to open the door and let the player out. OpenDoor also interacts with Openable_Door_BP under BuldingEscape/Content to alow a smooth opening of the door. As well as playing the opening sound. 
