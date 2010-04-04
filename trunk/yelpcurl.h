#ifndef __YELPCURL_H__
#define __YELPCURL_H__

#include "curl/curl.h"
#include <string>

/* Constants used in yelpCurl */
namespace yelpCurlDefaults
{
    const char YELPCURL_EOS = '\0';
    const int YELPCURL_DEFAULT_BUFFSIZE = 1024;
    const std::string YELPCURL_COLON = ":";
    const std::string YELPCURL_SPACE = "%20";
    const std::string YELPCURL_SEPARATOR = "&";
    const std::string YELPCURL_TLLAT = "&tl_lat=";
    const std::string YELPCURL_TLLONG = "&tl_long=";
    const std::string YELPCURL_BRLAT = "&br_lat=";
    const std::string YELPCURL_BRLONG = "&br_long=";
    const std::string YELPCURL_LIMIT = "&limit=";
    const std::string YELPCURL_YWSID = "&ywsid=";
    const std::string YELPCURL_LAT = "&lat=";
    const std::string YELPCURL_LONG = "&long=";
    const std::string YELPCURL_RADIUS = "&radius=";
    const std::string YELPCURL_LOCATION = "&location=";
    const std::string YELPCURL_LAT2 = "lat=";
    const std::string YELPCURL_LOCATION2 = "location=";
};

/* Yelp URLs */
namespace yelpUrls
{
    const std::string YELP_BUSINESS_REVIEW_SEARCH_URL = "http://api.yelp.com/business_review_search?term=";
    const std::string YELP_PHONE_SEARCH_URL = "http://api.yelp.com/phone_search?phone=";
    const std::string YELP_NEIGHBORHOOD_SEARCH_URL = "http://api.yelp.com/neighborhood_search?";
};

/* Generic struct used by various yelpCurl APIs */
typedef struct _yelpGenericParams
{
    int limit; /* search limit */
    double tl_lat; /* top left lattitude */
    double tl_long; /* top left longitude */
    double br_lat; /* bottom right lattitude */
    double br_long; /* bottom right longitude */
    double lat; /* lattitude */
    double longt; /* longitude */
    double radius; /* radius */
} yelpGenericParams;

/* yelpCurl class */
class yelpCurl
{
public:
    yelpCurl();
    ~yelpCurl();

    /* Yelp YWSID get/set APIs */
    std::string& getYelpWebServiceId();
    void setYelpWebServiceId( std::string& yelpWebSvcId );

    /* Yelp Review Search APIs */
    bool reviewSearchByMapBoundingBox( std::string& searchTerm, yelpGenericParams& searchParams );
    bool reviewSearchByGeoPoint( std::string& searchTerm, yelpGenericParams& searchParams );
    bool reviewSearchByNieghborhood( std::string& searchTerm, std::string& searchLocation );

    /* Yelp Phone Search APIs */
    bool searchPhoneNumber( std::string& phoneNum );

    /* Yelp Neighborhood Search APIs */
    bool searchNeighborhoodByGeoCode( yelpGenericParams& searchParams );
    bool searchNeighborhoodByLocation( std::string& searchLocation );

    /* cURL APIs */
    bool isCurlInit();
    void getLastWebResponse( std::string& outWebResp );
    void getLastCurlError( std::string& outErrResp );
    
    /* cURL proxy get/set APIs */
    std::string& getProxyServerIp();
    std::string& getProxyServerPort();
    std::string& getProxyUserName();
    std::string& getProxyPassword();
    void setProxyServerIp( std::string& proxyServerIp );
    void setProxyServerPort( std::string& proxyServerPort );
    void setProxyUserName( std::string& proxyUserName );
    void setProxyPassword( std::string& proxyPassword );
    
    /* Internal cURL methods */
    int saveLastWebResponse( char*& data, size_t size );
    static int curlCallback( char* data, size_t size, size_t nmemb, yelpCurl* pYelpCurlObj );

private:
    /* cURL data */
    CURL* m_curlHandle;
    char m_errorBuffer[yelpCurlDefaults::YELPCURL_DEFAULT_BUFFSIZE];
    std::string m_callbackData;
    
    /* cURL flags */
    bool m_curlProxyParamsSet;
    bool m_curlCallbackParamsSet;
    
    /* cURL proxy data */
    std::string m_proxyServerIp;
    std::string m_proxyServerPort;
    std::string m_proxyUserName;
    std::string m_proxyPassword;

    /* Yelp data */
    std::string m_yelpWebSvcId;

private:
    /* Private methods used by yelpcurl */
    void clearCurlCallbackBuffers();
    void prepareCurlProxy();
    void prepareCurlCallback();
    void prepareStandardParams();
    bool performGet( const std::string& getUrl );
};

/* Private utility functions */
void utilMakeCurlParams( std::string& outStr, std::string& inParam1, std::string& inParam2 );
void utilTrimSpaces( std::string& inStr, std::string& outStr );

#endif