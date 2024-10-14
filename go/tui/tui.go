package tui

import (
	"os"

	tea "github.com/charmbracelet/bubbletea"
	"github.com/koki-morino/pt/logger"
)

type tui struct {
	f       *os.File
	l       *logger.Logger
	model   *model
	program *tea.Program
}

func Tui() (*tui, error) {
	if err := os.MkdirAll("log", os.ModePerm); err != nil {
		return nil, err
	}

	f, err := os.OpenFile("log/tui.log", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		return nil, err
	}

	l := logger.New(f)

	model, err := Model(f, l)
	if err != nil {
		return nil, err
	}

	return &tui{
		f,
		l,
		model,
		tea.NewProgram(model, tea.WithAltScreen()),
	}, nil
}

func (t tui) Close() {
	t.f.Close()
}

func (t tui) Run() error {
	t.l.Debug("App is running.")

	_, err := t.program.Run()
	if err != nil {
		return err
	}

	t.l.Debug("App has terminated.")

	return nil
}
