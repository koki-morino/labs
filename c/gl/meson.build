project(
    'gl',
    'c',
    version: '1.0.0',
    default_options: [
        'c_std=c11',
    ]
)

deps = [
    dependency('sdl2'),
    dependency('epoxy'),
]

executable('gl', 'src/main.c', dependencies : deps)
