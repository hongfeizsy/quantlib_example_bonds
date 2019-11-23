#include <iostream>
#include <boost/timer.hpp>
#include <ql/quantlib.hpp>

int main() {
	boost::timer timer;
	// Building of the Libor forecasting curve
	// deposits
	QuantLib::Rate d1wQuote = 0.043375;
	QuantLib::Rate d1mQuote = 0.031875;
	QuantLib::Rate d3mQuote = 0.0320375;
	QuantLib::Rate d6mQuote = 0.03385;
	QuantLib::Rate d9mQuote = 0.0338125;
	QuantLib::Rate d1yQuote = 0.0335125;
	// swaps
	QuantLib::Rate s2yQuote = 0.0295;
	QuantLib::Rate s3yQuote = 0.0323;
	QuantLib::Rate s5yQuote = 0.0359;
	QuantLib::Rate s10yQuote = 0.0412;
	QuantLib::Rate s15yQuote = 0.0433;
	// deposits
	boost::shared_ptr<QuantLib::Quote> d1wRate(new QuantLib::SimpleQuote(d1wQuote));
	boost::shared_ptr<QuantLib::Quote> d1mRate(new QuantLib::SimpleQuote(d1mQuote));
	boost::shared_ptr<QuantLib::Quote> d3mRate(new QuantLib::SimpleQuote(d3mQuote));
	boost::shared_ptr<QuantLib::Quote> d6mRate(new QuantLib::SimpleQuote(d6mQuote));
	boost::shared_ptr<QuantLib::Quote> d9mRate(new QuantLib::SimpleQuote(d9mQuote));
	boost::shared_ptr<QuantLib::Quote> d1yRate(new QuantLib::SimpleQuote(d1yQuote));
	// swaps
	boost::shared_ptr<QuantLib::Quote> s2yRate(new QuantLib::SimpleQuote(s2yQuote));
	boost::shared_ptr<QuantLib::Quote> s3yRate(new QuantLib::SimpleQuote(s3yQuote));
	boost::shared_ptr<QuantLib::Quote> s5yRate(new QuantLib::SimpleQuote(s5yQuote));
	boost::shared_ptr<QuantLib::Quote> s10yRate(new QuantLib::SimpleQuote(s10yQuote));
	boost::shared_ptr<QuantLib::Quote> s15yRate(new QuantLib::SimpleQuote(s15yQuote));

	// Rate helpers
	// deposits
	QuantLib::Natural fixingDays = 3;
	QuantLib::Calendar calendar = QuantLib::TARGET();
	QuantLib::DayCounter depositDayCounter = QuantLib::Actual360();
	QuantLib::DayCounter zcBondsDayCounter = QuantLib::Actual365Fixed();
	boost::shared_ptr<QuantLib::RateHelper> d1w = boost::make_shared<QuantLib::DepositRateHelper>(QuantLib::Handle<QuantLib::Quote>(d1wRate), 
		QuantLib::Period(1, QuantLib::Weeks), fixingDays, calendar, QuantLib::ModifiedFollowing, true, zcBondsDayCounter);
	boost::shared_ptr<QuantLib::RateHelper> d1m = boost::make_shared<QuantLib::DepositRateHelper>(QuantLib::Handle<QuantLib::Quote>(d1mRate),
		QuantLib::Period(1, QuantLib::Months), fixingDays, calendar, QuantLib::ModifiedFollowing, true, zcBondsDayCounter);
	boost::shared_ptr<QuantLib::RateHelper> d3m = boost::make_shared<QuantLib::DepositRateHelper>(QuantLib::Handle<QuantLib::Quote>(d3mRate),
		QuantLib::Period(3, QuantLib::Months), fixingDays, calendar, QuantLib::ModifiedFollowing, true, zcBondsDayCounter);
	boost::shared_ptr<QuantLib::RateHelper> d6m = boost::make_shared<QuantLib::DepositRateHelper>(QuantLib::Handle<QuantLib::Quote>(d6mRate),
		QuantLib::Period(6, QuantLib::Months), fixingDays, calendar, QuantLib::ModifiedFollowing, true, zcBondsDayCounter);
	boost::shared_ptr<QuantLib::RateHelper> d9m = boost::make_shared<QuantLib::DepositRateHelper>(QuantLib::Handle<QuantLib::Quote>(d9mRate),
		QuantLib::Period(9, QuantLib::Months), fixingDays, calendar, QuantLib::ModifiedFollowing, true, zcBondsDayCounter);
	boost::shared_ptr<QuantLib::RateHelper> d1y = boost::make_shared<QuantLib::DepositRateHelper>(QuantLib::Handle<QuantLib::Quote>(d1yRate),
		QuantLib::Period(12, QuantLib::Months), fixingDays, calendar, QuantLib::ModifiedFollowing, true, zcBondsDayCounter);
	// swap rates
	QuantLib::Frequency fixedFrequency = QuantLib::Annual;
	QuantLib::BusinessDayConvention fixedDayConvention = QuantLib::Unadjusted;
	QuantLib::DayCounter fixedDayCounter = QuantLib::Thirty360();
	boost::shared_ptr<QuantLib::IborIndex> iborIndex = boost::make_shared<QuantLib::Euribor6M>();
	QuantLib::Period fwdStart(3, QuantLib::Days);
	boost::shared_ptr<QuantLib::RateHelper> swap2y = boost::make_shared<QuantLib::SwapRateHelper>(QuantLib::Handle<QuantLib::Quote>(s2yRate), 
		QuantLib::Period(2, QuantLib::Years), calendar, fixedFrequency, fixedDayConvention, fixedDayCounter, iborIndex, 
		QuantLib::Handle<QuantLib::Quote>(), fwdStart);
	boost::shared_ptr<QuantLib::RateHelper> swap3y = boost::make_shared<QuantLib::SwapRateHelper>(QuantLib::Handle<QuantLib::Quote>(s3yRate),
		QuantLib::Period(3, QuantLib::Years), calendar, fixedFrequency, fixedDayConvention, fixedDayCounter, iborIndex,
		QuantLib::Handle<QuantLib::Quote>(), fwdStart);
	boost::shared_ptr<QuantLib::RateHelper> swap5y = boost::make_shared<QuantLib::SwapRateHelper>(QuantLib::Handle<QuantLib::Quote>(s5yRate),
		QuantLib::Period(5, QuantLib::Years), calendar, fixedFrequency, fixedDayConvention, fixedDayCounter, iborIndex,
		QuantLib::Handle<QuantLib::Quote>(), fwdStart);
	boost::shared_ptr<QuantLib::RateHelper> swap10y = boost::make_shared<QuantLib::SwapRateHelper>(QuantLib::Handle<QuantLib::Quote>(s10yRate),
		QuantLib::Period(10, QuantLib::Years), calendar, fixedFrequency, fixedDayConvention, fixedDayCounter, iborIndex,
		QuantLib::Handle<QuantLib::Quote>(), fwdStart);
	boost::shared_ptr<QuantLib::RateHelper> swap15y = boost::make_shared<QuantLib::SwapRateHelper>(QuantLib::Handle<QuantLib::Quote>(s15yRate),
		QuantLib::Period(15, QuantLib::Years), calendar, fixedFrequency, fixedDayConvention, fixedDayCounter, iborIndex,
		QuantLib::Handle<QuantLib::Quote>(), fwdStart);
	// curve building
	std::vector<boost::shared_ptr<QuantLib::RateHelper>> depoSwapInstruments;
	depoSwapInstruments.push_back(d1w);
	depoSwapInstruments.push_back(d1m);
	depoSwapInstruments.push_back(d3m);
	depoSwapInstruments.push_back(d6m);
	depoSwapInstruments.push_back(d9m);
	depoSwapInstruments.push_back(d1y);
	depoSwapInstruments.push_back(swap2y);
	depoSwapInstruments.push_back(swap3y);
	depoSwapInstruments.push_back(swap5y);
	depoSwapInstruments.push_back(swap10y);
	depoSwapInstruments.push_back(swap15y);

	QuantLib::Date settlementDate = QuantLib::Date(18, QuantLib::September, 2008);
	settlementDate = calendar.adjust(settlementDate);
	QuantLib::DayCounter dayCounter = QuantLib::ActualActual(QuantLib::ActualActual::ISDA);
	boost::shared_ptr<QuantLib::YieldTermStructure> depoSwapTermStructure = boost::make_shared<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>(
		settlementDate, depoSwapInstruments, dayCounter, 1.0e-15
		);
	
	std::cout << depoSwapTermStructure->discount(15) << std::endl;

	std::cout << "Computing time: " << timer.elapsed() << " seconds" << std::endl;
 	return 0;
}

//int main()
//{
//	boost::timer timer;
//
//	// market data
//	QuantLib::Calendar calendar = QuantLib::TARGET();
//	QuantLib::Date settlementDate(18, QuantLib::September, 2019);
//	settlementDate = calendar.adjust(settlementDate);
//	QuantLib::Integer fixingDays = 3;
//	QuantLib::Natural settlementDays = 3;
//
//	QuantLib::Date todaysDate = calendar.advance(settlementDate, -fixingDays, QuantLib::Days);
//	QuantLib::Settings::instance().evaluationDate() = todaysDate;
//
//	//std::cout << "Today: " << todaysDate.weekday() << ", " << todaysDate << std::endl;
//	//std::cout << "Settlement date: " << settlementDate.weekday() << ", " << settlementDate << std::endl;
//	
//	// building of bonds discounting yield curve
//
//	// ZC rates for the short end
//	QuantLib::Rate zc3mQuote = 0.0096;
//	QuantLib::Rate zc6mQuote = 0.0145;
//	QuantLib::Rate zc1yQuote = 0.0194;
//
//	boost::shared_ptr<QuantLib::Quote> zc3mRate(new QuantLib::SimpleQuote(zc3mQuote));
//	boost::shared_ptr<QuantLib::Quote> zc6mRate(new QuantLib::SimpleQuote(zc6mQuote));
//	boost::shared_ptr<QuantLib::Quote> zc1yRate(new QuantLib::SimpleQuote(zc1yQuote));
//
//	QuantLib::DayCounter zcBondDayCounter = QuantLib::Actual365Fixed();
//
//	boost::shared_ptr<QuantLib::RateHelper> zc3m(new QuantLib::DepositRateHelper(QuantLib::Handle<QuantLib::Quote>(zc3mRate), 
//		QuantLib::Period(3, QuantLib::Months), settlementDays, calendar, QuantLib::ModifiedFollowing, true, zcBondDayCounter));
//	boost::shared_ptr<QuantLib::RateHelper> zc6m(new QuantLib::DepositRateHelper(QuantLib::Handle<QuantLib::Quote>(zc6mRate),
//		QuantLib::Period(6, QuantLib::Months), settlementDays, calendar, QuantLib::ModifiedFollowing, true, zcBondDayCounter));
//	boost::shared_ptr<QuantLib::RateHelper> zc1y(new QuantLib::DepositRateHelper(QuantLib::Handle<QuantLib::Quote>(zc1yRate),
//		QuantLib::Period(1, QuantLib::Years), settlementDays, calendar, QuantLib::ModifiedFollowing, true, zcBondDayCounter));
//
//	// setup bonds
//	QuantLib::Real redemption = 100.0;
//	
//	const QuantLib::Size numberOfBonds = 5;
//
//	QuantLib::Date issueDates[] = {
//		QuantLib::Date(15, QuantLib::March, 2005),
//		QuantLib::Date(15, QuantLib::June, 2005),
//		QuantLib::Date(30, QuantLib::June, 2006),
//		QuantLib::Date(15, QuantLib::November, 2002),
//		QuantLib::Date(15, QuantLib::May, 1987)
//	};
//
//	QuantLib::Date maturities[] = {
//		QuantLib::Date(31, QuantLib::August, 2010),
//		QuantLib::Date(31, QuantLib::August, 2011),
//		QuantLib::Date(31, QuantLib::August, 2013),
//		QuantLib::Date(15, QuantLib::August, 2018),
//		QuantLib::Date(15, QuantLib::May, 2038)
//	};
//
//	QuantLib::Real couponRates[] = {
//		0.02375,
//		0.04725,
//		0.03125,
//		0.04000,
//		0.04500
//	};
//
//	QuantLib::Real marketQuotes[] = {
//		100.390625,
//		106.21875,
//		100.59375,
//		101.6875,
//		102.140625
//	};
//
//	std::vector<boost::shared_ptr<QuantLib::SimpleQuote>> quote(numberOfBonds);
//	for (QuantLib::Size i = 0; i < quote.size(); i++) {
//		quote[i] = boost::make_shared<QuantLib::SimpleQuote>(marketQuotes[i]);
//	}
//
//	QuantLib::RelinkableHandle<QuantLib::Quote> quoteHandle[numberOfBonds];
//	for (QuantLib::Size i = 0; i < numberOfBonds; i++) {
//		quoteHandle[i].linkTo(quote[i]);
//	}
//
//	// definition of rate helpers
//	std::vector<boost::shared_ptr<QuantLib::BondHelper>> bondsHelpers;
//	for (QuantLib::Size i = 0; i < numberOfBonds; i++) {
//		QuantLib::Schedule schedule(issueDates[i], maturities[i], QuantLib::Period(QuantLib::Semiannual), QuantLib::TARGET(), 
//			QuantLib::Unadjusted, QuantLib::Unadjusted, QuantLib::DateGeneration::Backward, false);
//		
//		boost::shared_ptr<QuantLib::FixedRateBondHelper> bondHelper(new QuantLib::FixedRateBondHelper(quoteHandle[i], 
//			settlementDays, 100.0, schedule, std::vector<QuantLib::Rate>(1, couponRates[i]), 
//			QuantLib::ActualActual(QuantLib::ActualActual::Bond), QuantLib::Unadjusted, redemption, issueDates[i]));
//
//		bondsHelpers.push_back(bondHelper);
//	}
//	std::cout << bondsHelpers[0]->maturityDate() << std::endl;
//
//	// Curve building
//	QuantLib::DayCounter termStructureDayCounter = QuantLib::ActualActual(QuantLib::ActualActual::ISDA);
//	double tolerance = 1.0e-15;
//
//	// A depo-bond curve
//	std::vector<boost::shared_ptr<QuantLib::RateHelper>> bondInstruments;
//	// Adding the fixed rate bonds to the curve for the short end
//	bondInstruments.push_back(zc3m);
//	bondInstruments.push_back(zc6m);
//	bondInstruments.push_back(zc1y);
//	
//	// Adding the fixed rate bonds to the curve for the short end
//	for (QuantLib::Size i = 0; i < numberOfBonds; i++) {
//		bondInstruments.push_back(bondsHelpers[i]);
//	}
//
//
//
//	std::cout << "Computation time: " << timer.elapsed() << " second" << std::endl;
//	return 0;
//}

