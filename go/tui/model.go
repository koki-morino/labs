package tui

import (
	"os"

	tea "github.com/charmbracelet/bubbletea"
	"github.com/charmbracelet/x/term"
	"github.com/koki-morino/pt/logger"
)

type model struct {
	state    tab
	curPos   curPos
	termSize termSize
	f        *os.File
	l        *logger.Logger
}

type curPos struct {
	x int
	y int
}

type termSize struct {
	width  int
	height int
}

func Model(f *os.File, l *logger.Logger) (*model, error) {
	width, height, err := term.GetSize(os.Stdout.Fd())
	if err != nil {
		return nil, err
	}

	return &model{
		connections,
		curPos{
			x: 0,
			y: 0,
		},
		termSize{
			width:  width,
			height: height,
		},
		f,
		l,
	}, nil
}

func (m model) Init() tea.Cmd {
	return nil
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {

	case tea.WindowSizeMsg:
		width, height, err := term.GetSize(os.Stdout.Fd())
		if err != nil {
			m.l.Error("Failed to get terminal size")
		}
		m.termSize = termSize{
			width:  width,
			height: height,
		}

	case tea.KeyMsg:
		switch msg.String() {

		case "ctrl+c", "q":
			return m, tea.Quit

		case "up":
			if m.curPos.y > 0 {
				m.curPos.y--
			}

		case "down":
			if m.curPos.y < 10 {
				m.curPos.y++
			}

		case "tab":
			m.state = m.tabNext(m.state)

		case "shift+tab":
			m.state = m.tabPrev(m.state)

		}

	}

	return m, nil
}

func (m model) View() string {
	s := ""
	for i := connections; i <= query; i++ {
		if i == m.state {
			s += CurrentTabTitleStyle.Render(tabTitle[i])
		} else {
			s += tabTitle[i]
		}
		s += " "
	}
	s += "\n\n"

	s += "Enter q to quit"

	return s
}
