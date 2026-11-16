#ifndef REPORT_H
#define REPORT_H

class Report {
public:
    void menu() const;

private:
    void categorySummary() const;
    void collectionSummary() const;
    void monthlySummary() const;
    void capacityAlerts() const;
};

#endif
