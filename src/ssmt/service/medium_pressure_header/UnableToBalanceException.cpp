#include "ssmt/service/medium_pressure_header/UnableToBalanceException.h"

UnableToBalanceException::UnableToBalanceException(const std::string &message) : message(message) {}

std::ostream &operator<<(std::ostream &stream, const UnableToBalanceException &e) {
    return stream << "UnableToBalanceException[" << "message=" << e.message << "]";
}

const std::string &UnableToBalanceException::getMessage() const {
    return message;
}
