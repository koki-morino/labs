project(
    'gl',
    'c',
    version: '1.0.0',
    default_options: [
        'c_std=c11',
        'warning_level=1',
    ]
)

deps = [
    dependency('sdl2'),
    dependency('glesv2'),
    dependency('fontconfig'),
]

sources = files(
    'src/font.c',
    'src/shader.c',
)

executable('graphics', 'src/main.c', sources, dependencies : deps)
