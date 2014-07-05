#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <asio_http/http_server.hpp>
#include <asio_http/http_client.hpp>
#include "json/json.h"

using namespace boost::asio::ip;

#define HTTP_404_TEMPLATE "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">\n" \
	"<title>404 Not Found</title>\n" \
	"<h1>Not Found</h1>\n" \
	"<p>The requested URL was not found on the server.  If you entered the URL manually please check your spelling and try again.</p>\n"

struct http_request_handler
{
	typedef basic_http_connection<http_request_handler> connection;
	void operator()(connection::pointer ptr)
	{
		if (ptr->get_request_url() == "/get")
		{
			std::cout << "Request handler" << std::endl;
			Json::Value result;
			result["url"] = ptr->get_request_url();
			Json::Value headers;
			std::ostringstream oss;
			for (connection::headers_type::const_iterator it = ptr->get_headers().begin(), end = ptr->get_headers().end();
				it != end; ++it)
			{
				headers[it->first] = it->second;
			}
			result["headers"] = headers;
			ptr->send_response(200, result.toStyledString());
			return;
		}
		ptr->send_response(404, HTTP_404_TEMPLATE);
	}
};

struct F
{
	F()
		: io_service()
		, server(io_service, tcp::endpoint(tcp::v4(), 0))
		, client(boost::asio::use_service<http_client>(io_service))
	{
		std::ostringstream oss;
		oss << "http://127.0.0.1:" << server.get_acceptor().local_endpoint().port();
		base_url = oss.str();
	}
	~F()
	{
	}
	boost::asio::io_service io_service;
	typedef http_server<http_request_handler> server_type;
	server_type server;
	http_client & client;
	std::string base_url;
};

struct client_body_handler
{
	typedef void result_type;
	std::string & str_;
	client_body_handler(std::string & str)
		: str_(str)
	{
	}
	int operator()(const boost::system::error_code & ec, boost::asio::const_buffer buffer)
	{
		const char * data = boost::asio::buffer_cast<const char *>(buffer);
		std::size_t size = boost::asio::buffer_size(buffer);
		str_.append(data, data + size);
		return size;
	}
};

struct client_done_handler
{
	typedef void result_type;
	boost::system::error_code & ec_;
	client_done_handler(boost::system::error_code & ec)
		: ec_(ec)
	{
	}
	void operator()(const boost::system::error_code & ec)
	{
		ec_ = ec;
	}
};

typedef	http_client_connection<
	http_client::protocol_type,
	client_body_handler,
	client_done_handler> client_connection;

BOOST_FIXTURE_TEST_SUITE( s, F )

BOOST_AUTO_TEST_CASE( test_get1 )
{
	std::string data;
	boost::system::error_code ec;
	client_body_handler body(data);
	client_done_handler done(ec);

	client_connection::pointer connection = client.create_request(base_url + "/get", body, done);
	connection->start();
	io_service.run();
}

BOOST_AUTO_TEST_SUITE_END()
