package tui

type tab int

const (
	connections tab = iota
	databases
	tables
	query
)

var tabTitle = map[tab]string{
	connections: "Connections",
	databases:   "Databases",
	tables:      "Tables",
	query:       "Query",
}

func (m model) tabNext(tab tab) tab {
	switch tab {
	case connections:
		return databases
	case databases:
		return tables
	case tables:
		return query
	case query:
		return connections
	default:
		m.l.Error("Current tab is unknown.")
		return connections
	}
}

func (m model) tabPrev(tab tab) tab {
	switch tab {
	case connections:
		return query
	case databases:
		return connections
	case tables:
		return databases
	case query:
		return tables
	default:
		m.l.Error("Current tab is unknown.")
		return connections
	}
}
