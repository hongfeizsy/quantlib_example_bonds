#include <iostream>
#include <boost/timer.hpp>
#include <ql/quantlib.hpp>

int main()
{
	boost::timer timer;

	// market data
	QuantLib::Calendar calendar = QuantLib::TARGET();
	QuantLib::Date settlementDate(18, QuantLib::September, 2019);
	settlementDate = calendar.adjust(settlementDate);
	QuantLib::Integer fixingDays = 3;
	QuantLib::Natural settlementDays = 3;

	QuantLib::Date todaysDate = calendar.advance(settlementDate, -fixingDays, QuantLib::Days);
	QuantLib::Settings::instance().evaluationDate() = todaysDate;

	//std::cout << "Today: " << todaysDate.weekday() << ", " << todaysDate << std::endl;
	//std::cout << "Settlement date: " << settlementDate.weekday() << ", " << settlementDate << std::endl;
	
	// building of bonds discounting yield curve

	// ZC rates for the short end
	QuantLib::Rate zc3mQuote = 0.0096;
	QuantLib::Rate zc6mQuote = 0.0145;
	QuantLib::Rate zc1yQuote = 0.0194;

	boost::shared_ptr<QuantLib::Quote> zc3mRate(new QuantLib::SimpleQuote(zc3mQuote));
	boost::shared_ptr<QuantLib::Quote> zc6mRate(new QuantLib::SimpleQuote(zc6mQuote));
	boost::shared_ptr<QuantLib::Quote> zc1yRate(new QuantLib::SimpleQuote(zc1yQuote));

	QuantLib::DayCounter zcBondDayCounter = QuantLib::Actual365Fixed();

	boost::shared_ptr<QuantLib::RateHelper> zc3m(new QuantLib::DepositRateHelper(QuantLib::Handle<QuantLib::Quote>(zc3mRate), 
		QuantLib::Period(3, QuantLib::Months), settlementDays, calendar, QuantLib::ModifiedFollowing, true, zcBondDayCounter));
	boost::shared_ptr<QuantLib::RateHelper> zc6m(new QuantLib::DepositRateHelper(QuantLib::Handle<QuantLib::Quote>(zc6mRate),
		QuantLib::Period(6, QuantLib::Months), settlementDays, calendar, QuantLib::ModifiedFollowing, true, zcBondDayCounter));
	boost::shared_ptr<QuantLib::RateHelper> zc1y(new QuantLib::DepositRateHelper(QuantLib::Handle<QuantLib::Quote>(zc1yRate),
		QuantLib::Period(1, QuantLib::Years), settlementDays, calendar, QuantLib::ModifiedFollowing, true, zcBondDayCounter));

	// setup bonds
	QuantLib::Real redemption = 100.0;
	
	const QuantLib::Size numberOfBonds = 5;

	QuantLib::Date issueDates[] = {
		QuantLib::Date(15, QuantLib::March, 2005),
		QuantLib::Date(15, QuantLib::June, 2005),
		QuantLib::Date(30, QuantLib::June, 2006),
		QuantLib::Date(15, QuantLib::November, 2002),
		QuantLib::Date(15, QuantLib::May, 1987)
	};

	QuantLib::Date maturities[] = {
		QuantLib::Date(31, QuantLib::August, 2010),
		QuantLib::Date(31, QuantLib::August, 2011),
		QuantLib::Date(31, QuantLib::August, 2013),
		QuantLib::Date(15, QuantLib::August, 2018),
		QuantLib::Date(15, QuantLib::May, 2038)
	};

	QuantLib::Real couponRates[] = {
		0.02375,
		0.04725,
		0.03125,
		0.04000,
		0.04500
	};

	QuantLib::Real marketQuotes[] = {
		100.390625,
		106.21875,
		100.59375,
		101.6875,
		102.140625
	};
	
	std::vector<boost::shared_ptr<QuantLib::SimpleQuote>> quote(numberOfBonds);
	for (QuantLib::Size i = 0; i < quote.size(); i++) {
		quote[i] = boost::make_shared<QuantLib::SimpleQuote>(marketQuotes[i]);
	}

	std::cout << "Computation time: " << timer.elapsed() << " second" << std::endl;
	return 0;
}

