/**
 * ...
 * @author Mike Parilla
 */

class MainMenuClass 
{
	
	
	public function MainMenuClass()
	{
		Unknown MainMenuClass: {code}
		static var NewGameButton:MainMenuClass;
		static var LoadGameButton:MainMenuClass;
		static var OptionsButton:MainMenuClass;
		static var ExitButton:MainMenuClass;
		public static function main(mc:MovieClip):Void
		{
			NewGameButton = new MainMenuClass();
			LoadGameButton = new MainMenuClass();
			OptionsButton = new MainMenuClass();
			ExitButton = new MainMenuClass();
		}
		Unknown MainMenuClass: {code}
		public function MainMenuClass() 
		{
			_root.ButtonClick.onPress = function()

			Unknown MainMenuClass: { fscommand(“ButtonClickPressed”); }
		}
		Unknown macro: {code}
		public static function ChangeMessage(message:String)
		{
			_root.MessageLabel.text = message;
		}
		Unknown macro: {code}
		class ButtonTestClass
		{
		static var NewGameButton:MainMenuClass;
		static var LoadGameButton:MainMenuClass;
		static var OptionsButton:MainMenuClass;
		static var ExitButton:MainMenuClass;

		public static function main(mc:MovieClip):Void

		Unknown macro: {	NewGameButton = new MainMenuClass();
							LoadGameButton = new MainMenuClass();
							OptionsButton = new MainMenuClass();
							ExitButton = new MainMenuClass();	}
		public function MainMenuClass() 
		{
		_root.ButtonClick.onPress = function()

		Unknown MainMenuClass: {	 fscommand("ButtonClickPressed"); }
		}

		public static function ChangeMessage(message:String)

		Unknown macro: {	 _root.MessageLabel.text = message;	}
		}
	}
}