#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "mlpairs.hpp"  // Include the header file for OpticsPairs class

// For CSV reading
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Function to read CSV file and convert to DataFrame
DataFrame readCSV(const std::string& filename, bool hasIndex = true, bool parseDates = true) {
    DataFrame df;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Read header
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string cell;
    std::vector<std::string> headers;
    
    // Skip index column if present
    if (hasIndex) {
        std::getline(ss, cell, ',');
    }
    
    // Read column headers
    while (std::getline(ss, cell, ',')) {
        headers.push_back(cell);
    }
    df.setHeaders(headers);

    // Read data rows
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string dateStr;
        std::vector<double> row;
        
        if (hasIndex) {
            std::getline(ss, dateStr, ',');
            if (parseDates) {
                // Convert date string to timestamp
                // This is a simplified version - you'd want more robust date parsing
                std::tm tm = {};
                std::istringstream dateStream(dateStr);
                dateStream >> std::get_time(&tm, "%Y-%m-%d");
                df.addTimestamp(std::mktime(&tm));
            }
        }
        
        // Read numeric values
        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        df.addRow(row);
    }
    
    return df;
}

int main() {
    try {
        // Disable warning output
        // Note: In C++ you might want to implement a more sophisticated warning system
        
        // Read stock prices from CSV
        std::string filename = "stock_data/2023-10-01_2024-12-04_top300sp500.csv";
        DataFrame stock_prices = readCSV(filename, true, true);
        
        // Create OpticsPairs instance
        OpticsPairs op(stock_prices);
        
        // Reduce dimensionality using PCA
        op.reducePCA();
        
        // Plot loadings
        op.plotLoadings();
        
        // Plot explained variance
        op.plotExplainedVariance();
        
        // Calculate and print total variance explained
        double total_variance_explained = 0.0;
        const std::vector<double>& variance_ratio = op.getExplainedVarianceRatio();
        for (double ratio : variance_ratio) {
            total_variance_explained += ratio;
        }
        std::cout << "Total variance explained: " 
                  << std::fixed << std::setprecision(2) 
                  << total_variance_explained * 100 << "%" << std::endl;
        
        // Find pairs
        op.findPairs();
        
        // Print pairs
        const auto& pairs = op.getPairs();
        std::cout << "Found pairs:" << std::endl;
        for (const auto& pair : pairs) {
            std::cout << pair.first << " - " << pair.second << std::endl;
        }
        
        // Plot clusters in 3D
        op.plotClusters(3);
        
        // Calculate various metrics
        op.calcEngleGrangerNormSpreads();
        op.calcHurstExponents();
        op.calcHalfLives();
        op.calcAvgCrossCount();
        
        // Filter pairs
        op.filterPairs();
        
        // Print filtered pairs
        const auto& filtered = op.getFilteredPairs();
        std::cout << "Filtered pairs:" << std::endl;
        for (const auto& pair : filtered) {
            std::cout << pair.toString() << std::endl;
        }
        
        // Plot pair price spreads for filtered pairs
        for (size_t i = 0; i < filtered.size(); ++i) {
            op.plotPairPriceSpread(i);
        }
        
        // Wait for user input
        std::cout << "Press Enter to continue...";
        std::cin.get();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
