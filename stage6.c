#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define constants
#define MAX_JOB_TITLE_LENGTH 100
#define MAX_JOB_FIELD_LENGTH 100
#define MAX_QUALIFICATIONS_LENGTH 500
#define MAX_NETWORK_NAME_LENGTH 50
#define MAX_API_KEY_LENGTH 100
#define MAX_API_URL_LENGTH 200
#define DATE_LENGTH 11  // "YYYY-MM-DD\0"

// Structure to store the job advertisement details
typedef struct {
    int id;
    char title[MAX_JOB_TITLE_LENGTH];
    char posting_date[DATE_LENGTH];
    char deadline[DATE_LENGTH];
    int number_of_hires;
    char job_field[MAX_JOB_FIELD_LENGTH];
    char qualifications[MAX_QUALIFICATIONS_LENGTH];
} JobPosting;

// Structure to store social network API details
typedef struct {
    char network_name[MAX_NETWORK_NAME_LENGTH];
    char api_key[MAX_API_KEY_LENGTH];
    char api_url[MAX_API_URL_LENGTH];
} SocialNetworkAPI;

// Job postings array and counter
JobPosting *jobPostings = NULL;
int totalJobPostings = 0;

// Social network list
SocialNetworkAPI socialNetworks[] = {
    {"Facebook", "API_KEY_FACEBOOK", "https://facebook.com/api"},
    {"Instagram", "API_KEY_INSTAGRAM", "https://instagram.com/api"},
    {"Thread", "API_KEY_THREAD", "https://thread.com/api"},
    {"LinkedIn", "API_KEY_LINKEDIN", "https://linkedin.com/api"},
    {"X", "API_KEY_X", "https://x.com/api"}
};
int totalSocialNetworks = 5;

// Function to get the current date in YYYY-MM-DD format
void getCurrentDate(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date_str, DATE_LENGTH, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// Function to compare two dates (YYYY-MM-DD)
int compareDates(const char *date1, const char *date2) {
    int y1, m1, d1, y2, m2, d2;
    sscanf(date1, "%d-%d-%d", &y1, &m1, &d1);
    sscanf(date2, "%d-%d-%d", &y2, &m2, &d2);
    
    if (y1 != y2) return y1 - y2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}

// Function to create a job posting
void createJobPosting() {
    jobPostings = realloc(jobPostings, (totalJobPostings + 1) * sizeof(JobPosting));
    if (!jobPostings) {
        printf("Memory allocation failed.\n");
        return;
    }

    JobPosting *job = &jobPostings[totalJobPostings];
    job->id = totalJobPostings + 1;

    printf("Enter job title: ");
    fgets(job->title, MAX_JOB_TITLE_LENGTH, stdin);
    job->title[strcspn(job->title, "\n")] = 0;  // Remove newline character

    printf("Enter posting date (YYYY-MM-DD): ");
    fgets(job->posting_date, DATE_LENGTH, stdin);
    job->posting_date[strcspn(job->posting_date, "\n")] = 0;

    printf("Enter deadline (YYYY-MM-DD): ");
    fgets(job->deadline, DATE_LENGTH, stdin);
    job->deadline[strcspn(job->deadline, "\n")] = 0;

    printf("Enter number of hires: ");
    scanf("%d", &job->number_of_hires);
    getchar();  // Consume the newline character

    printf("Enter job field: ");
    fgets(job->job_field, MAX_JOB_FIELD_LENGTH, stdin);
    job->job_field[strcspn(job->job_field, "\n")] = 0;

    printf("Enter qualifications: ");
    fgets(job->qualifications, MAX_QUALIFICATIONS_LENGTH, stdin);
    job->qualifications[strcspn(job->qualifications, "\n")] = 0;

    totalJobPostings++;
    printf("Job posting created successfully with ID %d.\n", job->id);
}

// Function to view job postings, excluding expired ones
void viewJobPostings() {
    char current_date[DATE_LENGTH];
    getCurrentDate(current_date);

    printf("\nJob Postings:\n");
    for (int i = 0; i < totalJobPostings; i++) {
        if (compareDates(jobPostings[i].deadline, current_date) < 0) {
            // Skip expired job postings
            continue;
        }

        printf("ID: %d, Title: %s, Posting Date: %s, Deadline: %s\n",
               jobPostings[i].id,
               jobPostings[i].title,
               jobPostings[i].posting_date,
               jobPostings[i].deadline);
    }

    if (totalJobPostings == 0) {
        printf("No job postings found.\n");
    }
}

// Function to view expired job postings
void viewExpiredJobPostings() {
    char current_date[DATE_LENGTH];
    getCurrentDate(current_date);

    printf("\nExpired Job Postings:\n");
    for (int i = 0; i < totalJobPostings; i++) {
        if (compareDates(jobPostings[i].deadline, current_date) >= 0) {
            // Skip non-expired job postings
            continue;
        }

        printf("ID: %d, Title: %s, Posting Date: %s, Deadline: %s\n",
               jobPostings[i].id,
               jobPostings[i].title,
               jobPostings[i].posting_date,
               jobPostings[i].deadline);
    }

    if (totalJobPostings == 0) {
        printf("No expired job postings found.\n");
    }
}

// Stub function for posting job ads on social networks
void postOnSocialNetworks() {
    printf("\nSocial Networks:\n");
    for (int i = 0; i < totalSocialNetworks; i++) {
        printf("%d. %s\n", i + 1, socialNetworks[i].network_name);
    }

    printf("Select a social network to post the job ad (1-%d): ", totalSocialNetworks);
    int choice;
    scanf("%d", &choice);
    getchar();  // Consume newline character

    if (choice < 1 || choice > totalSocialNetworks) {
        printf("Invalid selection.\n");
        return;
    }

    int job_id;
    printf("Enter job ad ID to post: ");
    scanf("%d", &job_id);

    if (job_id < 1 || job_id > totalJobPostings) {
        printf("Invalid job ad ID.\n");
        return;
    }
//hb inject
    // Posting job ad (stub function)
    printf("Posting job ad #%d on %s...\n", job_id, socialNetworks[choice - 1].network_name);
    printf("API URL: %s\n", socialNetworks[choice - 1].api_url);
    printf("API Key: %s\n", socialNetworks[choice - 1].api_key);
    printf("Job ad posted successfully!\n");
}

// Main function to execute the program
void findSpecialist() {
    while (1) {
        printf("\n[Menu]\n");
        printf("1. Create Job Posting\n");
        printf("2. View Job Postings\n");
        printf("3. View Expired Job Postings\n");
        printf("4. Post on Social Networks\n");
        printf("5. Exit\n");

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character

        switch (choice) {
            case 1:
                createJobPosting();
                break;
            case 2:
                viewJobPostings();
                break;
            case 3:
                viewExpiredJobPostings();
                break;
            case 4:
                postOnSocialNetworks();
                break;
            case 5:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    findSpecialist();
    return 0;
}
