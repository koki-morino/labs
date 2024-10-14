package tui

import "github.com/charmbracelet/lipgloss"

var (
	CurrentTabTitleStyle = lipgloss.NewStyle().Bold(true).Underline(true)
	ErrorStyle           = lipgloss.NewStyle().Foreground(lipgloss.Color("204"))
)
