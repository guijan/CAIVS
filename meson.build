project('CAIVS', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c99'])

if host_machine.system().endswith('bsd') or host_machine.system() == 'cygwin' or host_machine.system() == 'darwin'
  libbsd_dep = dependency('', required: false)
else
  add_project_arguments('-D_POSIX_C_SOURCE=200809L', language : 'c')
  libbsd_dep = dependency('libbsd-overlay')
endif

executable('CAIVS',
           'caivs.c',
           install : true,
           dependencies : libbsd_dep)
