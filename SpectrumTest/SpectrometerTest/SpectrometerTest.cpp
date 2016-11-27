/* File:    SpectrumTest.cpp
 * Author:  Ocean Optics Inc.        JK
 *
 * Date: 03/13/2008
 *
 * Revised: 04/08/2008
 *
 * Note:
 * This code is provided as-is for illustration purposes only.  
 * Use this code at your own risk.
 * This program written to use the OmniDriver files and demonstrate the aquisition 
 * of a spectrum using the "Wrapper" API.
 */


#include <stdio.h>

#include "ArrayTypes.h" // located in %OMNIDRIVER_HOME%\include
#include "Wrapper.h"

int main()
{
	int		integrationTime = 100000;		//The integration time in µs
	int		numberOfPixels;
	int		numberOfSpectrometersAttached; // actually attached and talking to us
	int		spectrometerIndex; // 0-n, identifies which spectrometer we are interacting with
	WRAPPER_T	wrapperHandle;

	printf("\nSpectrumTest Demo 1.03\n");
	printf("language: C/C++\n");
	printf("OmniDriver interface type: \"C\"\n");
	printf("API demonstrated: Wrapper\n");

	wrapperHandle = Wrapper_Create();

	// The following call will populate an internal array of spectrometer objects 
	numberOfSpectrometersAttached = Wrapper_openAllSpectrometers(wrapperHandle);
	printf("\nnumber of spectrometers found = %d\n",numberOfSpectrometersAttached);
	if (numberOfSpectrometersAttached == 0)
		return 0; // there are no attached spectrometers
	
	// We will arbitrarily use the first attached spectrometer
	spectrometerIndex = 0;


	// Display some information about this spectrometer
	JSTRING firmwareVersion = JString_Create();
	JSTRING serialNumber = JString_Create();
	JSTRING spectrometerName = JString_Create();
	Wrapper_getSerialNumber(wrapperHandle,spectrometerIndex,serialNumber);
	Wrapper_getName(wrapperHandle,spectrometerIndex,spectrometerName);
	Wrapper_getFirmwareVersion(wrapperHandle,spectrometerIndex,firmwareVersion);
	printf("spectrometer type: %s   serial number: %s  firmware version: %s\n",
		JString_getASCII(spectrometerName),
		JString_getASCII(serialNumber),
		JString_getASCII(firmwareVersion));
	JString_Destroy(firmwareVersion);
	JString_Destroy(serialNumber);
	JString_Destroy(spectrometerName);


	Wrapper_setIntegrationTime(wrapperHandle,spectrometerIndex,integrationTime);
	printf("The integration time of the first spectrometer has been set to 100ms\n");

	// Now aquire a spectrum
	printf ("\nPress <enter> to get a spectrum from this spectrometer\n");
	getchar();

	DOUBLEARRAY_T spectrumArrayHandle = DoubleArray_Create();
	Wrapper_getSpectrum(wrapperHandle,spectrometerIndex,spectrumArrayHandle);
	double* spectrumValues = DoubleArray_getDoubleValues(spectrumArrayHandle);
	numberOfPixels = DoubleArray_getLength(spectrumArrayHandle);

	DOUBLEARRAY_T wavelengthArrayHandle = DoubleArray_Create();
	Wrapper_getWavelengths(wrapperHandle,spectrometerIndex,wavelengthArrayHandle);
	double* wavelengthValues = DoubleArray_getDoubleValues(wavelengthArrayHandle);

	// Loop to print the spectral data to the screen
	for (int i = 0; i<numberOfPixels; i++)
	{
		printf("wavelength(nm): %1.2f Intensity: %5.2f\n",wavelengthValues[i],spectrumValues[i]);
	}
	DoubleArray_Destroy(spectrumArrayHandle);
	DoubleArray_Destroy(wavelengthArrayHandle);

	// Clean up
	Wrapper_closeAllSpectrometers(wrapperHandle);

	Wrapper_Destroy(wrapperHandle);

	printf("\nPress <enter> to exit the app normally\n");
	getchar();
}
