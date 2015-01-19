#include <gtest/gtest.h>

#include <Las/LasFile.hpp>
#include <Las/LasFileParser.hpp>

#include <Uni/Logging/Logging>

#include <QApplication>
#include <QFile>
#include <QSharedPointer>

TEST(ImportLas, Las12) {
  Geo::Import::LasFileParser parser;

  // construct las file name
  QString fileName = QString("%1/../tests/%2").
                     arg(QCoreApplication::applicationDirPath()).
                     arg("sample_minimal.las");

  ASSERT_TRUE(QFile::exists(fileName));

  // parsing
  QSharedPointer<Geo::Import::LasFile> lasFile = parser.parse(fileName);

  // check well information
  ASSERT_TRUE(lasFile->lasRequired.wellName ==
              QString("ANY ET AL A9-16-49-20"));

  // check some key numbers
  ASSERT_FLOAT_EQ(635.0, lasFile->logMetrics.start);
  ASSERT_FLOAT_EQ(400.0, lasFile->logMetrics.stop);
  ASSERT_FLOAT_EQ(-0.1250, lasFile->logMetrics.step);
  ASSERT_FLOAT_EQ(-999.25, lasFile->logMetrics.nullValue);

  // check total number of additional entries
  ASSERT_EQ(0, lasFile->wellInformation.size());

  // check some required values and their values
  ASSERT_TRUE(lasFile->lasRequired.field == "EDAM");
  ASSERT_TRUE(lasFile->lasRequired.location == "A9-16-49-20W3M");
  ASSERT_TRUE(lasFile->lasRequired.province == "SASKATCHEWAN");

  // check curve information
  ASSERT_EQ(8, lasFile->logInformation.size());

  ASSERT_TRUE(lasFile->logInformation["RHOB"].units == "K/M3");
  ASSERT_TRUE(lasFile->logInformation["SFLA"].description ==
              "SHALLOW RESISTIVITY");

  ASSERT_TRUE(lasFile->data["SFLA"].size() == lasFile->data["ILD"].size());
}

//// -----------------------------

TEST(ImportLas, Las20) {
  Geo::Import::LasFileParser parser;

  // construct las file name
  QString fileName = QString("%1/../tests/%2").
                     arg(QCoreApplication::applicationDirPath()).
                     arg("sample_2.0_minimal.las");

  ASSERT_TRUE(QFile::exists(fileName));

  // parsing
  QSharedPointer<Geo::Import::LasFile> lasFile = parser.parse(fileName);

  // check well information
  ASSERT_TRUE(lasFile->lasRequired.wellName ==
              QString("ANY ET AL 12-34-12-34"));

  ASSERT_FLOAT_EQ(635.0, lasFile->logMetrics.start);
  ASSERT_FLOAT_EQ(400.0, lasFile->logMetrics.stop);

  // check total number of additional entries
  ASSERT_EQ(0, lasFile->wellInformation.size());

  ASSERT_TRUE(lasFile->lasRequired.field == "WILDCAT");
  ASSERT_TRUE(lasFile->lasRequired.location == "12-34-12-34W5M");
  ASSERT_TRUE(lasFile->lasRequired.province == "ALBERTA");

  // check curve information
  ASSERT_EQ(8, lasFile->logInformation.size());

  ASSERT_TRUE(lasFile->logInformation["RHOB"].units == "K/M3");
  ASSERT_TRUE(lasFile->logInformation["SFLA"].description ==
              "SHALLOW RESISTIVITY");

  ASSERT_TRUE(lasFile->data["SFLA"].size() == lasFile->data["ILD"].size());
}
