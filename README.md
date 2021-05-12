# ORCAunio
Single header file with namespace for communicating with ORCA (Object-oriented Real-time Control and Acquisition). 

http://orca.physics.unc.edu/

Note:

CmdMessenger won't compile for some boards due to an error returning '\0' on a char function. Simply replace '\0' with 0 on line 448 of CmdMessenger.cpp.
