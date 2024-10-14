using Common;

namespace Desktop.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    public string Title => Constants.Title;
    public string Greeting => "Welcome to Avalonia!";
}
