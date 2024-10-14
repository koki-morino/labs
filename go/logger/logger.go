package logger

import (
	"fmt"
	"os"
	"time"
)

type Logger struct {
	f *os.File
}

func New(file *os.File) *Logger {
	return &Logger{file}
}

func (l *Logger) Debug(format string, v ...any) {
	currentDatetime := time.Now().UTC().Format(time.RFC3339)
	fmt.Fprintf(l.f, "["+currentDatetime+"] DEBUG: "+format+"\n", v...)
}

func (l *Logger) Info(format string, v ...any) {
	currentDatetime := time.Now().UTC().Format(time.RFC3339)
	fmt.Fprintf(l.f, "["+currentDatetime+"] INFO: "+format+"\n", v...)
}

func (l *Logger) Warn(format string, v ...any) {
	currentDatetime := time.Now().UTC().Format(time.RFC3339)
	fmt.Fprintf(l.f, "["+currentDatetime+"] WARN: "+format+"\n", v...)
}

func (l *Logger) Error(format string, v ...any) {
	currentDatetime := time.Now().UTC().Format(time.RFC3339)
	fmt.Fprintf(l.f, "["+currentDatetime+"] ERROR: "+format+"\n", v...)
}

func (l *Logger) Fatal(v ...any) {
	currentDatetime := time.Now().UTC().Format(time.RFC3339)
	s := fmt.Sprint(v...)
	fmt.Fprintf(l.f, "["+currentDatetime+"] FATAL: "+s+"\n")
	os.Exit(1)
}

func (l *Logger) Panic(v ...any) {
	currentDatetime := time.Now().UTC().Format(time.RFC3339)
	s := fmt.Sprint(v...)
	fmt.Fprintf(l.f, "["+currentDatetime+"] PANIC: "+s+"\n")
	panic(s)
}
