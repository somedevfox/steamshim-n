project('steamshim-n', 'cpp',
    version: '0.1.0'
)

cc = meson.get_compiler('cpp')
base_dir = meson.current_source_dir()

# Find Steamworks API DLL for specific system
steam_include_directories = include_directories('./sdk/public')
steam_library_dir = ''
steam_library_name = ''
sdk_bin_path = base_dir + '/sdk/redistributable_bin/'

system = build_machine.system()
cpuarch = build_machine.cpu()
if system == 'windows' or system == 'cygwin' # Windows NT
    if cpuarch == 'x86' or cpuarch == 'i386'
        steam_library_dir = sdk_bin_path
    else
        steam_library_dir = sdk_bin_path + 'win64'
    endif
elif system == 'linux' or system == 'freebsd' or system == 'netbsd' or system == 'gnu' # UNIX
    if cpuarch == 'x86' or cpuarch == 'i386'
        steam_library_dir = sdk_bin_path + '/linux32/'
    else
        steam_library_dir = sdk_bin_path + '/linux64/'
    endif
elif system == 'darwin' # macOS
    steam_library_dir = sdk_bin_path + '/osx/'
else # ???
    error('Unknown system!')
endif
if cpuarch == 'x86_64'
    if system == 'windows' or system == 'cygwin'
        steam_library_name = 'steam_api64'
    else
        steam_library_name = 'steam_api'
    endif
else 
    steam_library_name = 'steam_api'
endif
steam = cc.find_library(steam_library_name, 
    required: true,
    static: false,
    dirs: [steam_library_dir]
)

# Gather source code
subdir('source')

# Compile shim
executable(meson.project_name(),
    sources: sources,
    dependencies: steam,
    include_directories: steam_include_directories,
    c_args: ['-DSS_DEBUG']
)