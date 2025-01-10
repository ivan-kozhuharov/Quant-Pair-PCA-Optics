#include <vector>
#include <string>
#include <map>
#include <memory>
#include <Eigen/Dense>
#include <cmath>
#include <algorithm>
#include <iostream>

// Forward declarations of required libraries/classes
class PCA;
class OPTICS;
class DataFrame;

class OpticsPairs {
private:
    DataFrame prices;
    std::vector<std::string> securities;
    DataFrame returns;
    Eigen::MatrixXd returns_reduced;
    Eigen::MatrixXd components;
    int n_components;
    std::vector<double> explained_variance_ratio;
    std::vector<std::pair<std::string, std::string>> pairs;
    std::vector<double> engle_granger_tests;
    DataFrame norm_spreads;
    std::vector<double> hurst_exponents;
    std::vector<double> half_lives;
    std::vector<double> avg_cross_count;
    DataFrame pairs_df;
    DataFrame filtered_pairs;
    std::vector<int> cluster_labels;

    // Static helper methods
    static double calcZScore(const std::vector<double>& spread) {
        double mean = 0.0;
        double stddev = 0.0;
        
        // Calculate mean
        for (double val : spread) mean += val;
        mean /= spread.size();
        
        // Calculate standard deviation
        for (double val : spread) {
            stddev += (val - mean) * (val - mean);
        }
        stddev = std::sqrt(stddev / (spread.size() - 1));
        
        // Calculate z-score
        std::vector<double> zscore(spread.size());
        for (size_t i = 0; i < spread.size(); i++) {
            zscore[i] = (spread[i] - mean) / stddev;
        }
        return zscore[0]; // Return first value as example
    }

    static double calculateHurst(const std::vector<double>& normSpread) {
        std::vector<int> lags;
        for (int i = 2; i < 100; i++) lags.push_back(i);
        
        // Calculate variances of lagged differences
        std::vector<double> tau;
        for (int lag : lags) {
            std::vector<double> diffs;
            for (size_t i = lag; i < normSpread.size(); i++) {
                diffs.push_back(normSpread[i] - normSpread[i - lag]);
            }
            
            // Calculate standard deviation
            double variance = 0.0;
            for (double diff : diffs) variance += diff * diff;
            variance /= diffs.size();
            tau.push_back(std::sqrt(variance));
        }
        
        // Use linear fit to estimate Hurst exponent
        // This is a simplified version - in practice you'd want to use
        // a proper linear regression library
        double H = 0.5; // Placeholder - implement actual calculation
        return H;
    }

public:
    OpticsPairs(const DataFrame& data) 
        : prices(data) {
        // Initialize securities vector from data columns
        // Calculate returns as percentage change
        calculateReturns();
    }

    void reducePCA(int n_components = 10, bool useScaler = true, int randomState = 42) {
        if (returns.empty()) {
            throw std::runtime_error("Returns not found: input price dataframe into OpticsPairs instance");
        }

        if (n_components > 15) {
            std::cerr << "Warning: Maximum n_components recommended is 15" << std::endl;
        }

        // Implementation would use Eigen for PCA
        // This is a placeholder for the actual implementation
        std::unique_ptr<PCA> pca = std::make_unique<PCA>(n_components, randomState);
        // pca->fit_transform(returns);
        
        // Store results
        this->n_components = n_components;
        // Store other PCA results
    }

    void findPairs() {
        if (returns_reduced.size() == 0) {
            throw std::runtime_error("returns_reduced not found: must run reduce_PCA() before this function");
        }

        // Implementation would use OPTICS clustering algorithm
        std::unique_ptr<OPTICS> clustering = std::make_unique<OPTICS>();
        // clustering->fit(components.transpose());

        // Create pairs from clusters
        // This is a placeholder for the actual implementation
    }

    // Additional methods would be implemented similarly
    void calcEngleGrangerNormSpreads() {
        // Implementation
    }

    void calcHurstExponents() {
        // Implementation
    }

    void calcHalfLives() {
        // Implementation
    }

    void calcAvgCrossCount(double tradingYear = 252.0) {
        // Implementation
    }

    void filterPairs(double maxPvalue = 0.05,
                    double maxHurstExp = 0.5,
                    double maxHalfLife = 252.0,
                    double minHalfLife = 1.0,
                    double minAvgCross = 12.0) {
        // Implementation
    }

    // Plotting methods would need to be implemented using a C++ plotting library
    // such as matplotlib-cpp or similar
    void plotPairPriceSpread(int idx) {
        // Implementation using plotting library
    }

    void plotExplainedVariance() {
        // Implementation using plotting library
    }

    void plotLoadings(int n = 5) {
        // Implementation using plotting library
    }

    void plotClusters(int nDimensions = 2) {
        // Implementation using plotting library
    }
};
