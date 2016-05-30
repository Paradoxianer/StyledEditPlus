#include <Alert.h>

#include "OOffice.h"
#include "OOfficeWindow.h"
#include "globalDefinitions.h"

OOffice::OOffice() : BApplication("application/x-vnd.VyR-OOffice") {

	_oofficewindow = new OOfficeWindow(BRect(50,50,600,600),"OOffice",
	                                   B_TITLED_WINDOW_LOOK ,B_NORMAL_WINDOW_FEEL ,
	                                   0, B_CURRENT_WORKSPACE);
    _oofficewindow->Show();
    
}
void OOffice::AboutRequested(void) {

	BAlert *myAlert = new BAlert("About OOffice",
	                             "OOffice " OVERSION "\nLicensed to: " OLICENSE
	                             "\nBuild number: " OBUILD
	                             "\n\nThanks to:\n\n" OTHANKS
	                             ,"Ok", NULL, NULL, 
								B_WIDTH_AS_USUAL, B_EVEN_SPACING, B_INFO_ALERT); 
	myAlert->Go();


}


/**** main function ****/
int main(void)
{
	setbuf(stdout,0);

	OOffice *app = new OOffice();
	app->Run();

	delete app;

	return B_OK;
}
