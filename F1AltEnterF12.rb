#==============================================================================
# Chainsawkitten's Disable F1, Alt+Enter, F12 v1.0
#------------------------------------------------------------------------------
# Disable the use of F1, Alt+Enter and F12 by registering a hook which consumes
# keypress events as well as setting the keyboard state.
#==============================================================================

Win32API.new("System/F1AltEnterF12", "hook", "", "").call()