# Introduction #
yelpcurl is a pure C++ library for Yelp.com APIs. yelpcurl uses cURL library for handling HTTP requests and responses. yelpcurl has been tested on Microsoft Windows operating systems, although it works/should work fine on many other operating systems that has/support cURL.
<br>
Currently yelpcurl supports following Yelp.com APIs:<br>
<ul><li>Yelp Review Search API<br>
<ul><li>Searching by Map Bounding Box<br>
</li><li>Search by Geo-Point and Radius<br>
</li><li>Search by Neighborhood, Address and City<br>
</li></ul></li><li>Yelp Phone API<br>
</li><li>Yelp Neighborhood API<br>
<ul><li>Neighborhood Search By Geocode<br>
</li><li>Neighborhood Search By Location</li></ul></li></ul>

<h1>Source</h1>
yelpcurl library source (with Microsoft Visual C++ 6.0 workspace) is available in the repository in "Source" tab. Use SVN or tools like TortoiseSVN (<a href='http://tortoisesvn.net/'>http://tortoisesvn.net/</a>) to check-out and download files. The same source code in zip format, <b>yelpcurl.zip</b>, is available in "Downloads" section. An example application that uses yelpcurl library is also available in "Downloads" section.<br>
<br>
<br>
<h1>Note</h1>
<ul><li>Yelp.com requires YWSID (Yelp Web Service ID) in order to use Yelp APIs. YWSID can be obtained here: <a href='http://www.yelp.com/developers/documentation/faq'>http://www.yelp.com/developers/documentation/faq</a>
</li><li>yelpcurl returns the HTTP responses from Yelp.com as it is (i.e. in JSON format). You need to have a JSON parser to parse the responses. Check <a href='http://www.json.org/'>http://www.json.org/</a> for JSON parser libraries.<br>
<br>
<br>
<h1>Help Needed?</h1>
See wiki section for information related to building and using yelpcurl library.<br>
<a href='http://code.google.com/p/yelpcurl/wiki/WikiHowToUseYelpcurlLibrary'>http://code.google.com/p/yelpcurl/wiki/WikiHowToUseYelpcurlLibrary</a>
<br>
<br>
<h1>Info</h1>
More info on cURL can be found here: <a href='http://curl.haxx.se/'>http://curl.haxx.se/</a> <br>
More info on Yelp APIs can be found here: <a href='http://www.yelp.com/developers/documentation/technical_overview'>http://www.yelp.com/developers/documentation/technical_overview</a>