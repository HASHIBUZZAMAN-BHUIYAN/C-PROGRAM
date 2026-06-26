#include <stdio.h>
#include <stdlib.h>

#define MAX_CANDIDATES 6
#define MAX_FIELDS 11
#define BUF_LEN 100

char candidate01[MAX_FIELDS][BUF_LEN];
char candidate02[MAX_FIELDS][BUF_LEN];
char candidate03[MAX_FIELDS][BUF_LEN];
char candidate04[MAX_FIELDS][BUF_LEN];
char candidate05[MAX_FIELDS][BUF_LEN];
char candidate06[MAX_FIELDS][BUF_LEN];

char (*member_info[MAX_CANDIDATES])[BUF_LEN] = {
  candidate01, candidate02, candidate03,
  candidate04, candidate05, candidate06
};

/* Removes newline character from fgets input */
void
remove_newline (char *str)
{
  int i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '\n')
        {
          str[i] = '\0';
          break;
        }
      i++;
    }
}

/* Calculate age from DOB */
int
calculate_age (const char *dob)
{
  int year, month, day;
  int current_year = 2025, current_month = 4, current_day = 6;
  sscanf (dob, "%d/%d/%d", &year, &month, &day);
  int age = current_year - year;
  if (current_month < month || (current_month == month && current_day < day))
    {
      age--;
    }
  return age;
}

/* Basic string comparison */
int
string_equal (const char *a, const char *b)
{
  int i = 0;
  while (a[i] != '\0' && b[i] != '\0')
    {
      if (a[i] != b[i])
        return 0;
      i++;
    }
  return a[i] == b[i];
}

/* Input audition group name using getchar */
void
input_group_name (char *group_name)
{
  int i = 0;
  char c;
  printf ("Enter Audition Group Name: ");
  while ((c = getchar ()) != '\n' && c != EOF && i < BUF_LEN - 1)
    {
      group_name[i++] = c;
    }
  group_name[i] = '\0';
}

int
main (void)
{
  char group_name[BUF_LEN];
  int index = 0;

  input_group_name (group_name);

  printf ("\n####################################\n");
  printf ("[%s] Audition Candidate Data Entry\n", group_name);
  printf ("####################################\n");

  while (index < MAX_CANDIDATES)
    {
      printf ("\n[%s] Audition Candidate Data Entry.\n", group_name);
      printf ("---------------------------------\n");

      printf ("1. Name: ");
      fgets (member_info[index][0], BUF_LEN, stdin);
      remove_newline (member_info[index][0]);

      printf ("2. Date of Birth (YYYY/MM/DD format): ");
      fgets (member_info[index][1], BUF_LEN, stdin);
      remove_newline (member_info[index][1]);

      printf ("3. Gender (F for Female, M for Male): ");
      fgets (member_info[index][2], BUF_LEN, stdin);
      remove_newline (member_info[index][2]);

      printf ("4. Email: ");
      fgets (member_info[index][3], BUF_LEN, stdin);
      remove_newline (member_info[index][3]);

      printf ("5. Nationality: ");
      fgets (member_info[index][4], BUF_LEN, stdin);
      remove_newline (member_info[index][4]);

      printf ("6. BMI: ");
      fgets (member_info[index][5], BUF_LEN, stdin);
      remove_newline (member_info[index][5]);

      printf ("7. Primary Skill: ");
      fgets (member_info[index][6], BUF_LEN, stdin);
      remove_newline (member_info[index][6]);

      printf ("8. Secondary Skill: ");
      fgets (member_info[index][7], BUF_LEN, stdin);
      remove_newline (member_info[index][7]);

      printf ("9. Korean Proficiency Level (TOPIK): ");
      fgets (member_info[index][8], BUF_LEN, stdin);
      remove_newline (member_info[index][8]);

      printf ("10. MBTI: ");
      fgets (member_info[index][9], BUF_LEN, stdin);
      remove_newline (member_info[index][9]);

      printf ("11. Introduction: ");
      fgets (member_info[index][10], BUF_LEN, stdin);
      remove_newline (member_info[index][10]);

      index++;
    }

  printf ("\n####################################\n");
  printf ("[%s] Audition Candidate Data Review \n", group_name);
  printf ("####################################\n");
  printf ("=============================================================================================\n");
  printf ("Name             | DOB       | Gender | Email                    | Nationality | BMI  | Primary Skill   | Secondary Skill   | TOPIK  | MBTI  |\n");
  printf ("=============================================================================================\n");

  for (int i = 0; i < MAX_CANDIDATES; i++)
    {
      int age = calculate_age (member_info[i][1]);
      int y, m, d;
      sscanf (member_info[i][1], "%d/%d/%d", &y, &m, &d);
      char dob_compact[9];
      sprintf (dob_compact, "%04d%02d%02d", y, m, d);

      char topik_level[10];
      if (string_equal (member_info[i][8], "0"))
        {
          sprintf (topik_level, "Native");
        }
      else
        {
          sprintf (topik_level, "%s", member_info[i][8]);
        }

      printf ("%-13s (%2d)| %-9s| %-6s| %-22s| %-12s| %-5s| %-14s| %-16s| %-7s| %-5s|\n",
              member_info[i][0], age,
              dob_compact,
              member_info[i][2],
              member_info[i][3],
              member_info[i][4],
              member_info[i][5],
              member_info[i][6],
              member_info[i][7],
              topik_level,
              member_info[i][9]);

      printf ("---------------------------------------------------------------------------------------------\n");
      printf ("%s\n", member_info[i][10]);
      printf ("---------------------------------------------------------------------------------------------\n");
    }

  return 0;
}
