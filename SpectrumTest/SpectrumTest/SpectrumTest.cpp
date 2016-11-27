
/* File:    SpectrumTest.cpp
 * Author:  Ocean Optics Inc.        JK
 *
 * Date: 03/13/2008
 * Revised:  06/25/2012  SRS
 *
 * Note:
 * This code is provided as-is for illustration only.  Use this code at your own risk.
 * This program written to use the OmniDriver files and demonstrate the acquisition 
 * of a spectrum using the wrapper class.
 */


#include <stdio.h>
#include <conio.h>

#include "ArrayTypes.h"										// located in %OMNIDRIVER_HOME%\include
#include "Wrapper.h"

int main()
{	 
	//int integrationTime = 100000;							// the number of microseconds for the integration time
	int integrationTime = 500000;							// the number of microseconds for the integration time
	int	numberOfPixels;										// number of CCD elements/pixels provided by the spectrometer
	int numberOfSpectrometersAttached;						// actually attached and talking to us
	DoubleArray spectrumArray;								// pixel values from the CCD elements
	DoubleArray wavelengthArray;							// wavelengths (in nanometers) corresponding to each CCD element
	Wrapper wrapper;				// this is the object through which we will access all of Omnidriver's capabilities

	numberOfSpectrometersAttached = wrapper.openAllSpectrometers();	// Gets an array of spectrometer objects
	printf ("\n\nNumber of spectrometers found: %d\n", numberOfSpectrometersAttached);
	printf ("Press enter to continue...\n");
	getchar();
	if (numberOfSpectrometersAttached <= 0)
		return 0;										// there are no attached spectrometers

	for (int index=0; index<numberOfSpectrometersAttached; ++index)
	{
		printf("attached spectrometer serial number: %s\n",wrapper.getSerialNumber(index).getASCII());
	}
	printf("\n");

	wrapper.setIntegrationTime(0,integrationTime);		// Sets the integration time of the first spectrometer to 100ms
	printf ("Integration time of the first spectrometer has been set to %d microseconds\n", integrationTime);
	printf ("Press enter to get the spectrum from this spectrometer...\n");
	getchar();
	spectrumArray = wrapper.getSpectrum(0);						// Retreives the spectrum from the first spectrometer
	if (wrapper.getWrapperExtensions().isSpectrumValid(0) == false) {
		printf("Error occured during spectrum acquisition\n");
		return 0;
	}
	if (wrapper.getWrapperExtensions().isSpectrumValid(0) == true) {
		printf("Spectrum acquisition was successful\n");
	}
	wavelengthArray = wrapper.getWavelengths(0);			    // Retreives the wavelengths of the first spectrometer 
	numberOfPixels = spectrumArray.getLength();					// Sets numberOfPixels to the length of the spectrumArray 
	double *wavelengths = wavelengthArray.getDoubleValues();	// Sets a pointer to the values of the wavelength array 
	double *spectrum = spectrumArray.getDoubleValues();			// Sets a pointer to the values of the Spectrum array 
	for(int i = 0; i < numberOfPixels; i++){					// Loop to print the spectral data to the screen
		printf("Wavelength: %1.2f      Spectrum: %f \n", wavelengths[i], spectrum[i]); 
	}
	printf("Spectrum complete, press enter to exit the program...\n");
	getchar();
	return 0;
}