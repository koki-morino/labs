package main

import (
	"os"

	"github.com/koki-morino/pt/logger"
	"github.com/koki-morino/pt/tui"
)

var l = logger.New(os.Stdout)

func main() {
	t, err := tui.Tui()
	if err != nil {
		l.Fatal(err)
	}
	defer t.Close()

	if err := t.Run(); err != nil {
		l.Fatal(err)
	}
}
