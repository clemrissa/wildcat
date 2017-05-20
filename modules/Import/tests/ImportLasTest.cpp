#include <catch/catch.hpp>

#include <Las/LasFile>
#include <Las/LasFileParser>

#include <QtWidgets/QApplication>
#include <QtCore/QFile>

#include <memory>

TEST_CASE("Las12", "[import]")
{
  Geo::Import::LasFileParser parser;

  // construct las file name
  QString fileName = QString("%1/../tests/%2").
                     arg(QCoreApplication::applicationDirPath()).
                     arg("sample_minimal.las");

  REQUIRE(QFile::exists(fileName) == true);

  // parsing
  std::shared_ptr<Geo::Import::LasFile> lasFile = parser.parse(fileName);

  // check well information
  REQUIRE(lasFile->lasRequired.wellName == QString("ANY ET AL A9-16-49-20"));

  // check some key numbers
  REQUIRE(lasFile->logMetrics.start == Approx(635.0));
  REQUIRE(lasFile->logMetrics.stop == Approx(400.0));
  REQUIRE(lasFile->logMetrics.step == Approx(-0.1250));
  REQUIRE(lasFile->logMetrics.nullValue == Approx(-999.25));

  // check total number of additional entries
  REQUIRE(lasFile->wellInformation.size() == 0);

  // check some required values and their values
  REQUIRE(lasFile->lasRequired.field == "EDAM");
  REQUIRE(lasFile->lasRequired.location == "A9-16-49-20W3M");
  REQUIRE(lasFile->lasRequired.province == "SASKATCHEWAN");

  // check curve information
  REQUIRE(lasFile->logInformation.size() == 8);

  REQUIRE(lasFile->logInformation["RHOB"].units == "K/M3");
  REQUIRE(lasFile->logInformation["SFLA"].description ==
          "SHALLOW RESISTIVITY");

  REQUIRE(lasFile->data["SFLA"].size() == lasFile->data["ILD"].size());
}

//// -----------------------------

TEST_CASE("Las20", "[import]")
{
  Geo::Import::LasFileParser parser;

  // construct las file name
  QString fileName = QString("%1/../tests/%2").
                     arg(QCoreApplication::applicationDirPath()).
                     arg("sample_2.0_minimal.las");

  REQUIRE(QFile::exists(fileName) == true);

  // parsing
  std::shared_ptr<Geo::Import::LasFile> lasFile = parser.parse(fileName);

  // check well information
  REQUIRE(lasFile->lasRequired.wellName == QString("ANY ET AL 12-34-12-34"));

  REQUIRE(lasFile->logMetrics.start == Approx(635.0));
  REQUIRE(lasFile->logMetrics.stop == Approx(400.0));

  // check total number of additional entries
  REQUIRE(lasFile->wellInformation.size() == 0);

  REQUIRE(lasFile->lasRequired.field == "WILDCAT");
  REQUIRE(lasFile->lasRequired.location == "12-34-12-34W5M");
  REQUIRE(lasFile->lasRequired.province == "ALBERTA");

  // check curve information
  REQUIRE(lasFile->logInformation.size() == 8);

  REQUIRE(lasFile->logInformation["RHOB"].units == "K/M3");
  REQUIRE(lasFile->logInformation["SFLA"].description ==
          "SHALLOW RESISTIVITY");

  REQUIRE(lasFile->data["SFLA"].size() == lasFile->data["ILD"].size());
}
