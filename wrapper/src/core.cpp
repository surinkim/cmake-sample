#include "core.h"

#include <iostream>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace web::json;
using namespace concurrency::streams;       // Asynchronous streams


namespace lib
{

pplx::task<void> CallAsyncHttp( const std::wstring& url )
{
	http_client client(url);
	return client.request( methods::GET )
		.then( [] ( http_response response ) -> pplx::task<std::wstring>
	{
		std::wostringstream stream;
		stream.str( std::wstring() );
		stream << U( "Content Type : " ) << response.headers().content_type() << std::endl;
		stream << U( "Content Length : " ) << response.headers().content_length() << U( "bytes" ) << std::endl;
		std::wcout << stream.str();

		return response.extract_string();
	} )
		.then( [] ( pplx::task<std::wstring> previousTask )
	{
		std::wcout << previousTask.get().c_str() << std::endl;
	} );
}

bool Core::CallHttp( const std::wstring& url )
{
	CallAsyncHttp(url).wait();

	std::cout << std::endl << "-- CallHttp" << std::endl;

	return true;
}

}