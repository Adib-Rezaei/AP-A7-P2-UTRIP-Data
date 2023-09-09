#ifndef _IMPORTEXCEPTION_HPP_
#define _IMPORTEXCEPTION_HPP_

#define NOT_FOUND "Not Found"
#define BAD_REQUEST "Bad Request"
#define PERMISSION_DENIED "Permission Denied"
#define NOT_ENOUGH_CREDIT "Not Enough Credit"
#define NOT_ENOUGH_ROOM "Not Enough Room"
#define NO_RATING "No Rating"
#define INSUFFICIEND_RATINGS "insufficient Ratings"

class ImportException {
    public:
        ImportException(std::string _message){ message = _message; }
        std::string what(){ return message; }
    private:
        std::string message;
};

#endif