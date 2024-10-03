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
    dependency('epoxy'),
]

sources = files('src/shader.c')

executable('gl', 'src/main.c', sources, dependencies : deps)
