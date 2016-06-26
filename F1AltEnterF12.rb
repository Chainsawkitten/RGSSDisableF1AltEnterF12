#==============================================================================
# Chainsawkitten's Disable F1, Alt+Enter, F12 v1.1
#------------------------------------------------------------------------------
# Disable the use of F1, Alt+Enter and F12 by registering a hook which consumes
# keypress events as well as setting the keyboard state.
#==============================================================================

module CskDisable
  # Whether to disable F1. 0 = enable, 1 = disable.
  DISABLE_F1 = 1
  
  # Whether to disable F12. 0 = enable, 1 = disable.
  DISABLE_F12 = 1
  
  # Whether to disable Alt+Enter. 0 = enable, 1 = disable.
  DISABLE_ALT_ENTER = 1
end

Win32API.new("System/F1AltEnterF12", "hook", "III", "").call(
  CskDisable::DISABLE_F1,
  CskDisable::DISABLE_F12,
  CskDisable::DISABLE_ALT_ENTER)