project('app', 'cpp',
        default_options: ['cpp_std=c++17'])

qt = import('qt6')
qt_deps = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

qtprocessed = qt.preprocess(moc_headers: 'src/widget.h')

exe = executable('app', 'src/main.cpp', 'src/widget.cpp',
                 qtprocessed,
                 dependencies: qt_deps)
