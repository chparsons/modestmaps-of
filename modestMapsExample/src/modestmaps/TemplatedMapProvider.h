#ifndef TEMPLATEDMAPPROVIDER
#define TEMPLATEDMAPPROVIDER

#include "AbstractMapProvider.h"
#include "MercatorProjection.h"

class TemplatedMapProvider : public AbstractMapProvider {

  public:

    vector<string> subdomains;
    string baseurl;

    TemplatedMapProvider( string baseurl, vector<string> subdomains ): 
      // this is the projection and transform you'll want for any Google-style map tile source:
      AbstractMapProvider(new MercatorProjection(26, Transformation(1.068070779e7, 0.0, 3.355443185e7, 0.0, -1.068070890e7, 3.355443057e7)))
    {
      this->baseurl = baseurl;
      this->subdomains = subdomains;
    }

    int tileWidth() {
      return 256;
    }

    int tileHeight() {
      return 256;
    }

    vector<string> getTileUrls(Coordinate rawCoordinate) {
      vector<string> urls;
      if (rawCoordinate.row >= 0 && rawCoordinate.row < pow(2, rawCoordinate.zoom)) {
        Coordinate coordinate = sourceCoordinate(rawCoordinate);
        stringstream url;
        string subdomain = subdomains[(int)ofRandom(0, subdomains.size())];
        url << "http://" << subdomain << baseurl << (int)coordinate.zoom << "/" << (int)coordinate.column << "/" << (int)coordinate.row << ".png";
        cout << rawCoordinate << " --> " << url.str() << endl;
        urls.push_back(url.str());
      }
      return urls;
    }

};

#endif
