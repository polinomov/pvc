

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
int main()
{
	extern int SdlEntryPoint();
	SdlEntryPoint();
    return 0;
}

