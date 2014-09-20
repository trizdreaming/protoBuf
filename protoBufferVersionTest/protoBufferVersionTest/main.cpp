#include <iostream>
#include <fstream>
#include <string>

#include "MyPacket.pb.h"

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/text_format.h>

using namespace std;
using namespace google;

int main( void )
{
	MyPacket::Position inputPosition;
	float testX = 1.1f;
	float testY = 1.2f;
	float testZ = 1.3f;
	
	inputPosition.set_x( testX );
	inputPosition.set_y( testY );
	inputPosition.set_z( testZ );

	int bufSize = inputPosition.ByteSize();
	char* outputBuf = new char[bufSize];

	memset( outputBuf, 0, sizeof( char )*bufSize );

	protobuf::io::ArrayOutputStream os( outputBuf, bufSize );
	inputPosition.SerializeToZeroCopyStream( &os );

	protobuf::io::ArrayInputStream is( outputBuf, bufSize );
	MyPacket::Position outputPosition;
	outputPosition.ParseFromZeroCopyStream( &is );

	float x = outputPosition.x();

	printf_s( "%f \n", x );

	getchar();
	return 0;
}