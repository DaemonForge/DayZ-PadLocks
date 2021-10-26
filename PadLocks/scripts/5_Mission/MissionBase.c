modded class MissionBase extends MissionBaseWorld
{
	override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
                case PADLOCK_INTERFACE:
					Print("PADLOCK_INTERFACE Create");
                    menu = new PadlockInterface;
                    break;
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}