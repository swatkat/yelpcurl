#include "yelpcurl.h"

/*++
* @method: yelpCurl::yelpCurl
*
* @description: constructor
*
* @input: none
*
* @output: none
*
*--*/
yelpCurl::yelpCurl():
m_curlHandle( NULL ),
m_curlProxyParamsSet( false ),
m_curlCallbackParamsSet( false ),
m_proxyServerIp( "" ),
m_proxyServerPort( "" ),
m_proxyUserName( "" ),
m_proxyPassword( "" ),
m_yelpWebSvcId( "" )
{
    /* Clear error buffer */
    clearCurlCallbackBuffers();

    /* Initialize cURL */
    m_curlHandle = curl_easy_init();
    if( !isCurlInit() )
    {
        std::string dummyStr( "" );
        getLastCurlError( dummyStr );
    }
}

/*++
* @method: yelpCurl::~yelpCurl
*
* @description: destructor
*
* @input: none
*
* @output: none
*
*--*/
yelpCurl::~yelpCurl()
{
    /* Cleanup cURL */
    if( isCurlInit() )
    {
        curl_easy_cleanup( m_curlHandle );
        m_curlHandle = NULL;
    }
}

/*++
* @method: yelpCurl::isCurlInit
*
* @description: method to check if cURL is initialized properly
*
* @input: none
*
* @output: true if cURL is intialized, otherwise false
*
*--*/
bool yelpCurl::isCurlInit()
{
    return ( NULL != m_curlHandle ) ? true : false;
}

/*++
* @method: yelpCurl::clearCurlCallbackBuffers
*
* @description: method to clear callback buffers used by cURL. this is an
*               internal method and yelpCurl users need not use this.
*
* @input: none
*
* @output: none
*
* @remarks: internal method
*
*--*/
void yelpCurl::clearCurlCallbackBuffers()
{
    m_callbackData = "";
    memset( m_errorBuffer, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
}

/*++
* @method: yelpCurl::getLastCurlError
*
* @description: method to get cURL error response for most recent http request.
*               yelpCurl users can call this method if any of the Yelp API methods
*               return false.
*
* @input: outErrResp - string in which cURL's response is supplied back to caller
*
* @output: none
*
*--*/
void yelpCurl::getLastCurlError( std::string& outErrResp )
{
    m_errorBuffer[yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE-1] = yelpCurlDefaults::YELPCURL_EOS;
    outErrResp.assign( m_errorBuffer );
}

/*++
* @method: yelpCurl::getLastWebResponse
*
* @description: method to get Yelp's http response for the most recent request.
*               yelpCurl users need to call this method and parse the JSON
*               data returned by Yelp to see what has happened.
*
* @input: outWebResp - string in which Yelp's response is supplied back to caller
*
* @output: none
*
*--*/
void yelpCurl::getLastWebResponse( std::string& outWebResp )
{
    if( m_callbackData.length() )
    {
        outWebResp = m_callbackData;
    }
}

/*++
* @method: yelpCurl::getProxyServerIp
*
* @description: method to get proxy server IP address
*
* @input: none
*
* @output: proxy server IP address
*
*--*/
std::string& yelpCurl::getProxyServerIp()
{
    return m_proxyServerIp;
}

/*++
* @method: yelpCurl::getProxyServerPort
*
* @description: method to get proxy server port
*
* @input: none
*
* @output: proxy server port
*
*--*/
std::string& yelpCurl::getProxyServerPort()
{
    return m_proxyServerPort;
}

/*++
* @method: yelpCurl::getProxyUserName
*
* @description: method to get proxy user name
*
* @input: none
*
* @output: proxy server user name
*
*--*/
std::string& yelpCurl::getProxyUserName()
{
    return m_proxyUserName;
}

/*++
* @method: yelpCurl::getProxyPassword
*
* @description: method to get proxy server password
*
* @input: none
*
* @output: proxy server password
*
*--*/
std::string& yelpCurl::getProxyPassword()
{
    return m_proxyPassword;
}

/*++
* @method: yelpCurl::setProxyServerIp
*
* @description: method to set proxy server IP address
*
* @input: proxyServerIp
*
* @output: none
*
*--*/
void yelpCurl::setProxyServerIp( std::string& proxyServerIp )
{
    if( proxyServerIp.length() )
    {
        m_proxyServerIp = proxyServerIp;
        /*
         * Reset the flag so that next cURL http request
         * would set proxy details again into cURL.
         */
        m_curlProxyParamsSet = false;
    }
}

/*++
* @method: yelpCurl::setProxyServerPort
*
* @description: method to set proxy server port
*
* @input: proxyServerPort
*
* @output: none
*
*--*/
void yelpCurl::setProxyServerPort( std::string& proxyServerPort )
{
    if( proxyServerPort.length() )
    {
        m_proxyServerPort = proxyServerPort;
        /*
         * Reset the flag so that next cURL http request
         * would set proxy details again into cURL.
         */
        m_curlProxyParamsSet = false;
    }
}

/*++
* @method: yelpCurl::setProxyUserName
*
* @description: method to set proxy server username
*
* @input: proxyUserName
*
* @output: none
*
*--*/
void yelpCurl::setProxyUserName( std::string& proxyUserName )
{
    if( proxyUserName.length() )
    {
        m_proxyUserName = proxyUserName;
        /*
         * Reset the flag so that next cURL http request
         * would set proxy details again into cURL.
         */
        m_curlProxyParamsSet = false;
    }
}

/*++
* @method: yelpCurl::setProxyPassword
*
* @description: method to set proxy server password
*
* @input: proxyPassword
*
* @output: none
*
*--*/
void yelpCurl::setProxyPassword( std::string& proxyPassword )
{
    if( proxyPassword.length() )
    {
        m_proxyPassword = proxyPassword;
        /*
         * Reset the flag so that next cURL http request
         * would set proxy details again into cURL.
         */
        m_curlProxyParamsSet = false;
    }
}

/*++
* @method: yelpCurl::prepareCurlProxy
*
* @description: method to set proxy details into cURL. this is an internal method.
*               yelpCurl users should not use this method, instead use setProxyXxx
*               methods to set proxy server information.
*
* @input: none
*
* @output: none
*
* @remarks: internal method
*
*--*/
void yelpCurl::prepareCurlProxy()
{
    if( !m_curlProxyParamsSet && m_proxyUserName.length() && m_proxyPassword.length() )
    {
        /* Reset existing proxy details in cURL */
        curl_easy_setopt( m_curlHandle, CURLOPT_PROXY, NULL );
        curl_easy_setopt( m_curlHandle, CURLOPT_PROXYUSERPWD, NULL );

        /* Prepare username and password for proxy server */
        std::string proxyIpPort( "" );
        std::string proxyUserPass( "" );
        utilMakeCurlParams( proxyUserPass, getProxyUserName(), getProxyPassword() );
        utilMakeCurlParams( proxyIpPort, getProxyServerIp(), getProxyServerPort() );

        /* Set proxy details in cURL */
        curl_easy_setopt( m_curlHandle, CURLOPT_PROXY, proxyIpPort.c_str() );
        curl_easy_setopt( m_curlHandle, CURLOPT_PROXYUSERPWD, proxyUserPass.c_str() );
        curl_easy_setopt( m_curlHandle, CURLOPT_PROXYAUTH, (long)CURLAUTH_ANY );

        /* Set the flag to true indicating that proxy info is set in cURL */
        m_curlProxyParamsSet = true;
    }
}

/*++
* @method: yelpCurl::prepareCurlCallback
*
* @description: method to set callback details into cURL. this is an internal method.
*               yelpCurl users should not use this method.
*
* @input: none
*
* @output: none
*
* @remarks: internal method
*
*--*/
void yelpCurl::prepareCurlCallback()
{
    if( !m_curlCallbackParamsSet )
    {
        /* Set buffer to get error */
        curl_easy_setopt( m_curlHandle, CURLOPT_ERRORBUFFER, m_errorBuffer );

        /* Set callback function to get response */
        curl_easy_setopt( m_curlHandle, CURLOPT_WRITEFUNCTION, curlCallback );
        curl_easy_setopt( m_curlHandle, CURLOPT_WRITEDATA, this );

        /* Set the flag to true indicating that callback info is set in cURL */
        m_curlCallbackParamsSet = true;
    }
}

/*++
* @method: yelpCurl::prepareStandardParams
*
* @description: method to set standard params into cURL. this is an internal method.
*               yelpCurl users should not use this method.
*
* @input: none
*
* @output: none
*
* @remarks: internal method
*
*--*/
void yelpCurl::prepareStandardParams()
{
    /* Clear callback and error buffers */
    clearCurlCallbackBuffers();

    /* Prepare proxy */
    prepareCurlProxy();

    /* Prepare cURL callback data and error buffer */
    prepareCurlCallback();
}

/*++
* @method: yelpCurl::curlCallback
*
* @description: static method to get http response back from cURL.
*               this is an internal method, users of yelpCurl need not
*               use this.
*
* @input: as per cURL convention.
*
* @output: size of data stored in our buffer
*
* @remarks: internal method
*
*--*/
int yelpCurl::curlCallback( char* data, size_t size, size_t nmemb, yelpCurl* pYelpCurlObj )
{
    int writtenSize = 0;
    if( ( NULL != pYelpCurlObj ) && ( NULL != data ) )
    {
        /* Save http response in yelpCurl object's buffer */
        writtenSize = pYelpCurlObj->saveLastWebResponse( data, ( size*nmemb ) );
    }
    return writtenSize;
}

/*++
* @method: yelpCurl::saveLastWebResponse
*
* @description: method to save http responses. this is an internal method
*               and yelpCurl users need not use this.
*
* @input: data - character buffer from cURL,
*         size - size of character buffer
*
* @output: size of data stored in our buffer
*
* @remaks: internal method
*
*--*/
int yelpCurl::saveLastWebResponse(  char*& data, size_t size )
{
    int bytesWritten = 0;
    if( data && size )
    {
        /* Append data in our internal buffer */
        m_callbackData.append( data, size );
        bytesWritten = (int)size; 
    }
    return bytesWritten;
}

/*++
* @method: yelpCurl::performGet
*
* @description: method to send http GET request. this is an internal method.
*               yelpCurl users should not use this method.
*
* @input: getUrl - Yelp query URL
*
* @output: none
*
* @remarks: internal method
*
*--*/
bool yelpCurl::performGet( const std::string& getUrl )
{
    /* Prepare cURL params */
    prepareStandardParams();

    /* Set http request and url */
    curl_easy_setopt( m_curlHandle, CURLOPT_HTTPGET, 1 );
    curl_easy_setopt( m_curlHandle, CURLOPT_URL, getUrl.c_str() );

    /* Send http request */
    if( CURLE_OK == curl_easy_perform( m_curlHandle ) )
    {
        return true;
    }
    return false;
}

/*++
* @method: yelpCurl::getYelpWebServiceId
*
* @description: method to get Yelp web service id
*
* @input: none
*
* @output: Yelp web service id
*
*--*/
std::string& yelpCurl::getYelpWebServiceId()
{
    return m_yelpWebSvcId;
}

/*++
* @method: yelpCurl::setYelpWebServiceId
*
* @description: method to set Yelp web service id
*
* @input: Yelp web service id
*
* @output: none
*
*--*/
void yelpCurl::setYelpWebServiceId( std::string& yelpWebSvcId )
{
    if( yelpWebSvcId.length() )
    {
        m_yelpWebSvcId = yelpWebSvcId;
    }
}

/*++
* @method: yelpCurl::reviewSearchByMapBoundingBox
*
* @description: method to do review search by map bounding box.
*
* @input: searchTerm - Search term (ex: "coffee")
*         searchParams - Search params. Only following members of yelpGenericParams
*                        struct are needed to contain valid values:
*                        yelpGenericParams::tl_lat,
*                        yelpGenericParams::tl_long,
*                        yelpGenericParams::br_lat,
*                        yelpGenericParams::br_long,
*                        yelpGenericParams::limit
*
* @output: true if GET is success, otherwise false. This method does not check http
*          response by Yelp.
*
* @remarks: If this method returns true, then use yelpCurl::getLastWebResponse() to
*           get Yelp's JSON response.
*           If this method returns false, then use yelpCurl::getLastCurlError() to
*           get cURL's response.
*
*--*/
bool yelpCurl::reviewSearchByMapBoundingBox( std::string& searchTerm, yelpGenericParams& searchParams )
{
    bool retVal = false;

    /* Check if cURL is initialized and if we have correct YWSID */
    if( isCurlInit() && m_yelpWebSvcId.length() && searchTerm.length() )
    {
        std::string srchQuery( "" );
        std::string dummyStr2( "" );
        char dummyStr[yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE];

        /* Build search query URL */
        srchQuery = yelpUrls::YELP_BUSINESS_REVIEW_SEARCH_URL;

        utilTrimSpaces( searchTerm, dummyStr2 );
        srchQuery.append( dummyStr2.c_str() );

        srchQuery.append( yelpCurlDefaults::YELPCURL_TLLAT.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.tl_lat );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_TLLONG.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.tl_long );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_BRLAT.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.br_lat );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_BRLONG.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.br_long );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_LIMIT.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%d", searchParams.limit );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_YWSID.c_str() );
        srchQuery.append( m_yelpWebSvcId.c_str() );

        /* Perform HTTP GET */
        retVal = performGet( srchQuery );
    }
    return retVal;
}

/*++
* @method: yelpCurl::reviewSearchByGeoPoint
*
* @description: method to do review search by geo point and radius
*
* @input: searchTerm - Search term (ex: "coffee")
*         searchParams - Search params. Only following members of yelpGenericParams
*                        struct are needed to contain valid values:
*                        yelpGenericParams::lat,
*                        yelpGenericParams::longt,
*                        yelpGenericParams::radius,
*                        yelpGenericParams::limit
*
* @output: true if GET is success, otherwise false. This method does not check http
*          response by Yelp.
*
* @remarks: If this method returns true, then use yelpCurl::getLastWebResponse() to
*           get Yelp's JSON response.
*           If this method returns false, then use yelpCurl::getLastCurlError() to
*           get cURL's response.
*
*--*/
bool yelpCurl::reviewSearchByGeoPoint( std::string& searchTerm, yelpGenericParams& searchParams )
{
    bool retVal = false;

    /* Check if cURL is initialized and if we have correct YWSID */
    if( isCurlInit() && m_yelpWebSvcId.length() && searchTerm.length() )
    {
        std::string srchQuery( "" );
        std::string dummyStr2( "" );
        char dummyStr[yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE];

        /* Build search query */
        srchQuery = yelpUrls::YELP_BUSINESS_REVIEW_SEARCH_URL;

        utilTrimSpaces( searchTerm, dummyStr2 );
        srchQuery.append( dummyStr2.c_str() );

        srchQuery.append( yelpCurlDefaults::YELPCURL_LAT.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.lat );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_LONG.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.longt );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_RADIUS.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.radius );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_LIMIT.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%d", searchParams.limit );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_YWSID.c_str() );
        srchQuery.append( m_yelpWebSvcId.c_str() );

        /* Perform HTTP GET */
        retVal = performGet( srchQuery );
    }
    return retVal;
}

/*++
* @method: yelpCurl::reviewSearchByNieghborhood
*
* @description: method to do review search by neighborhood location.
*
* @input: searchTerm - Search term (ex: "coffee")
*         searchLocation - Search location (ex: "MG Road Bangalore India")
*
* @output: true if GET is success, otherwise false. This method does not check http
*          response by Yelp.
*
* @remarks: If this method returns true, then use yelpCurl::getLastWebResponse() to
*           get Yelp's JSON response.
*           If this method returns false, then use yelpCurl::getLastCurlError() to
*           get cURL's response.
*
*--*/
bool yelpCurl::reviewSearchByNieghborhood( std::string& searchTerm, std::string& searchLocation )
{
    bool retVal = false;

    /* Check if cURL is initialized and if we have correct YWSID */
    if( isCurlInit() && m_yelpWebSvcId.length() && searchTerm.length() && searchLocation.length() )
    {
        std::string srchQuery( "" );
        std::string dummyStr( "" );

        /* Build search query */
        srchQuery = yelpUrls::YELP_BUSINESS_REVIEW_SEARCH_URL;

        utilTrimSpaces( searchTerm, dummyStr );
        srchQuery.append( dummyStr.c_str() );

        dummyStr = "";
        utilTrimSpaces( searchLocation, dummyStr );
        srchQuery.append( yelpCurlDefaults::YELPCURL_LOCATION.c_str() );
        srchQuery.append( dummyStr.c_str() );

        srchQuery.append( yelpCurlDefaults::YELPCURL_YWSID.c_str() );
        srchQuery.append( m_yelpWebSvcId.c_str() );

        /* Perform HTTP GET */
        retVal = performGet( srchQuery );
    }
    return retVal;
}

/*++
* @method: yelpCurl::searchPhoneNumber
*
* @description: method to search by phone number
*
* @input: phoneNum - Phone number
*
* @output: true if GET is success, otherwise false. This method does not check http
*          response by Yelp.
*
* @remarks: If this method returns true, then use yelpCurl::getLastWebResponse() to
*           get Yelp's JSON response.
*           If this method returns false, then use yelpCurl::getLastCurlError() to
*           get cURL's response.
*
*--*/
bool yelpCurl::searchPhoneNumber( std::string& phoneNum )
{
    bool retVal = false;

    /* Check if cURL is initialized and if we have correct YWSID */
    if( isCurlInit() && m_yelpWebSvcId.length() && phoneNum.length() )
    {
        std::string srchQuery( "" );

        /* Build query URL */
        srchQuery = yelpUrls::YELP_PHONE_SEARCH_URL;
        srchQuery.append( phoneNum.c_str() );

        srchQuery.append( yelpCurlDefaults::YELPCURL_YWSID.c_str() );
        srchQuery.append( m_yelpWebSvcId.c_str() );

        /* Perform HTTP GET */
        retVal = performGet( srchQuery );
    }
    return retVal;
}

/*++
* @method: yelpCurl::searchNeighborhoodByGeoCode
*
* @description: method to search neighborhood by geo code
*
* @input: searchParams - Search params. Only following members of yelpGenericParams
*                        struct are needed to contain valid values:
*                        yelpGenericParams::lat,
*                        yelpGenericParams::longt
*
* @output: true if GET is success, otherwise false. This method does not check http
*          response by Yelp.
*
* @remarks: If this method returns true, then use yelpCurl::getLastWebResponse() to
*           get Yelp's JSON response.
*           If this method returns false, then use yelpCurl::getLastCurlError() to
*           get cURL's response.
*
*--*/
bool yelpCurl::searchNeighborhoodByGeoCode( yelpGenericParams& searchParams )
{
    bool retVal = false;

    /* Check if cURL is initialized and if we have correct YWSID */
    if( isCurlInit() && m_yelpWebSvcId.length() )
    {
        std::string srchQuery( "" );
        char dummyStr[yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE];

        /* Build query URL */
        srchQuery = yelpUrls::YELP_NEIGHBORHOOD_SEARCH_URL;

        srchQuery.append( yelpCurlDefaults::YELPCURL_LAT2.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.lat );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_LONG.c_str() );
        memset( dummyStr, 0, yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE );
        sprintf( dummyStr, "%f", searchParams.longt );
        srchQuery.append( dummyStr );

        srchQuery.append( yelpCurlDefaults::YELPCURL_YWSID.c_str() );
        srchQuery.append( m_yelpWebSvcId.c_str() );

        /* Perform HTTP GET */
        retVal = performGet( srchQuery );
    }
    return retVal;
}

/*++
* @method: yelpCurl::searchNeighborhoodByLocation
*
* @description: method to search neighborhood by location/address
*
* @input: searchLocation - Location string (ex: "MG Road Bangalore" )
*
* @output: true if GET is success, otherwise false. This method does not check http
*          response by Yelp.
*
* @remarks: If this method returns true, then use yelpCurl::getLastWebResponse() to
*           get Yelp's JSON response.
*           If this method returns false, then use yelpCurl::getLastCurlError() to
*           get cURL's response.
*
*--*/
bool yelpCurl::searchNeighborhoodByLocation( std::string& searchLocation )
{
    bool retVal = false;

    /* Check if cURL is initialized and if we have correct YWSID */
    if( isCurlInit() && m_yelpWebSvcId.length() )
    {
        std::string srchQuery( "" );
        std::string dummyStr( "" );

        /* Build query URL */
        srchQuery = yelpUrls::YELP_NEIGHBORHOOD_SEARCH_URL;

        utilTrimSpaces( searchLocation, dummyStr );
        srchQuery.append( yelpCurlDefaults::YELPCURL_LOCATION2.c_str() );
        srchQuery.append( dummyStr.c_str() );

        srchQuery.append( yelpCurlDefaults::YELPCURL_YWSID.c_str() );
        srchQuery.append( m_yelpWebSvcId.c_str() );

        /* Perform HTTP GET */
        retVal = performGet( srchQuery );
    }
    return retVal;
}

/*++
* @method: utilMakeCurlParams
*
* @description: utility function to build parameter strings in the format
*               required by cURL ("param1:param2"). yelpCurl users should
*               not use this function.
*
* @input: inParam1 - first parameter,
*         inParam2 - second parameter
*
* @output: outStr - built parameter
*
* @remarks: internal method
*
*--*/
void utilMakeCurlParams( std::string& outStr, std::string& inParam1, std::string& inParam2 )
{
    outStr = inParam1;
    outStr.append( yelpCurlDefaults::YELPCURL_COLON.c_str() );
    outStr.append( inParam2.c_str() );
}

/*++
* @method: utilTrimSpaces
*
* @description: utility function to replace space (' ') with %20
*
* @input: inStr - input string,
*         outStr - output string with space replaced by %20
*
* @output: outStr - built parameter
*
* @remarks: internal method
*
*--*/
void utilTrimSpaces( std::string& inStr, std::string& outStr )
{
    for( int i = 0; i < inStr.length(); i++ )
    {
        if( ' ' == inStr[i] )
        {
            outStr.append( yelpCurlDefaults::YELPCURL_SPACE.c_str() );
        }
        else
        {
            outStr.append( 1, inStr[i] );
        }
    }
}