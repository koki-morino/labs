using Common;

namespace Mobile;

public partial class AppShell : Shell
{
    public AppShell()
    {
        InitializeComponent();
        this.Title = Constants.Title;
    }
}
