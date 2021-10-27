class CfgPatches
{
  class PadLocks
  {
    requiredAddons[]={ "DZ_Data" }; 
  };
};

class CfgMods
{
  class PadLocks
  {
    name="PadLocks";
    type="mod"
	dependencies[]={ "Game", "World", "Mission" };
	class defs
	{
		class gameScriptModule
        {
			value = "";
            files[]={
				"PadLocks/scripts/3_Game"
			};
        };
		class worldScriptModule
        {
            value="";
            files[]={ 
				"PadLocks/scripts/4_World" 
			};
        };
	    class missionScriptModule
        {
            value="";
            files[]={
				"PadLocks/scripts/5_Mission" 
			};
        };
    };
  };
};
class CfgVehicles
{
	class Inventory_Base;
	class Padlock: Inventory_Base
	{
		scope = 2;
		displayName = "PadLock";
		descriptionShort = "A simple PadLock for locking your shit up";
		model = "PadLocks\data\Padlock.p3d";
		inventorySlot[] = {"Att_CombinationLock"};
		itemSize[] = {1,2};
		weight = 350;
		simpleHiddenSelections[] = {
			"FenceLock"
		};
        hiddenSelections[]=
        {
			"FenceLock"
        };
	};
};