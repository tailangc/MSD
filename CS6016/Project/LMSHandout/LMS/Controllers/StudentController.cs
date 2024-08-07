using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace LMS.Controllers
{
    [Authorize(Roles = "Student")]
    public class StudentController : Controller
    {
        private LMSContext db;
        public StudentController(LMSContext _db)
        {
            db = _db;
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Catalog()
        {
            return View();
        }

        public IActionResult Class(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            return View();
        }

        public IActionResult Assignment(string subject, string num, string season, string year, string cat, string aname)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            return View();
        }


        public IActionResult ClassListings(string subject, string num)
        {
            System.Diagnostics.Debug.WriteLine(subject + num);
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            return View();
        }


        /*******Begin code to modify********/

        /// <summary>
        /// Returns a JSON array of the classes the given student is enrolled in.
        /// Each object in the array should have the following fields:
        /// "subject" - The subject abbreviation of the class (such as "CS")
        /// "number" - The course number (such as 5530)
        /// "name" - The course name
        /// "season" - The season part of the semester
        /// "year" - The year part of the semester
        /// "grade" - The grade earned in the class, or "--" if one hasn't been assigned
        /// </summary>
        /// <param name="uid">The uid of the student</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetMyClasses(string uid)
        {
            var classes = db.Enrolleds
                .Where(e => e.StudentId == uid)
                .Select(e => new
                {
                    subject = e.Class.Course.Department.SubjectAbbreviation, // Accessing Course through Class
                    number = e.Class.Course.Number, //Accessing Course Number through Class Navigation property inside of enrolled 
                    name = e.Class.Course.Name, 
                    season = e.Class.SemesterSeason, // Accessing Semester properties directly from Class
                    year = e.Class.SemesterYear,
                    grade = e.Grade ?? "--" // Return "--" if no grade assigned
                })
                .ToList();

            return Json(classes);
        }

        /// <summary>
        /// Returns a JSON array of all the assignments in the given class that the given student is enrolled in.
        /// Each object in the array should have the following fields:
        /// "aname" - The assignment name
        /// "cname" - The category name that the assignment belongs to
        /// "due" - The due Date/Time
        /// "score" - The score earned by the student, or null if the student has not submitted to this assignment.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="uid"></param>
        /// <returns>The JSON array</returns>
        public IActionResult GetAssignmentsInClass(string subject, int num, string season, int year, string uid)
        {            
           var assignments = db.Assignments
                //Selects all assignments that are associated with this subject, course number, semester and  year
                .Where(a => a.Categories.Class.Course.Department.SubjectAbbreviation == subject && 
                            a.Categories.Class.Course.Number == num &&
                            a.Categories.Class.SemesterSeason == season && 
                            a.Categories.Class.SemesterYear == year)
                .Select(a => new
                {   //lists the assignment name, category and due date, and score for student (if completed)
                    aname = a.AssignmentName,
                    cname = a.Categories.CategoryName,
                    due = a.Due,
                    score = db.Submissions
                        .Where(s => s.AssignmentId == a.AssignmentId && s.StudentId == uid)
                        .Select(s => s.Score)
                        .FirstOrDefault()
                })
                .ToList();

            return Json(assignments);
        }




        /// <summary>
        /// Adds a submission to the given assignment for the given student
        /// The submission should use the current time as its DateTime
        /// You can get the current time with DateTime.Now
        /// The score of the submission should start as 0 until a Professor grades it
        /// If a Student submits to an assignment again, it should replace the submission contents
        /// and the submission time (the score should remain the same).
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The new assignment name</param>
        /// <param name="uid">The student submitting the assignment</param>
        /// <param name="contents">The text contents of the student's submission</param>
        /// <returns>A JSON object containing {success = true/false}</returns>
                public IActionResult SubmitAssignmentText(string subject, int num, string season, int year,
          string category, string asgname, string uid, string contents){
            // Retrieve the assignment based on the provided parameters.
            // Use a LINQ query to find the assignment that matches the provided details.
            var assignment = db.Assignments
                .FirstOrDefault(a => a.Categories.Class.Course.Department.SubjectAbbreviation == subject &&
                                    a.Categories.Class.Course.Number == num &&
                                    a.Categories.Class.SemesterSeason == season &&
                                    a.Categories.Class.SemesterYear == year &&
                                    a.Categories.CategoryName == category && 
                                    a.AssignmentName == asgname);

            // If the assignment is not found, return a JSON object with success = false.
            if (assignment == null) 
            {
                return Json(new { success = false });
            }

            // Retrieve the student's submission for this assignment.
            // Use a LINQ query to find the submission that matches the assignment ID and student ID.
            var submission = db.Submissions
                .FirstOrDefault(s => s.AssignmentId == assignment.AssignmentId && s.StudentId == uid);

            if (submission != null)
            {
                // Update the existing submission.
                // If a submission already exists, update its contents and submission time.
                submission.Contents = contents;
                submission.Time = DateTime.Now;
            }
            else
            {
                // Create a new submission.
                // If no submission exists, create a new one with the provided details.
                submission = new Submission
                {
                    AssignmentId = assignment.AssignmentId,
                    StudentId = uid,
                    Contents = contents,
                    Time = DateTime.Now,
                    Score = 0 // Initial score is 0.
                };
                // Add the new submission to the database context.
                db.Submissions.Add(submission);
            }

            // Save the changes to the database.
            // Commit the changes to the database to persist the new or updated submission.
            db.SaveChanges();

            // Return a JSON object indicating success.
            return Json(new { success = true });
        }

        


        /// <summary>
        /// Enrolls a student in a class.
        /// </summary>
        /// <param name="subject">The department subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester</param>
        /// <param name="year">The year part of the semester</param>
        /// <param name="uid">The uid of the student</param>
        /// <returns>A JSON object containing {success = {true/false}. 
        /// false if the student is already enrolled in the class, true otherwise.</returns>
                public IActionResult Enroll(string subject, int num, string season, int year, string uid)
        {    
            var courseOffering = db.Classes
                .FirstOrDefault(co => co.Course.Department.SubjectAbbreviation == subject && co.Course.Number == num &&
                                    co.SemesterSeason == season && co.SemesterYear == year);

            Console.WriteLine("KT Made it here");
            if (courseOffering == null)
            {    Console.WriteLine("course offering is Null");
                return Json(new { success = false });
            }
            Console.WriteLine("After course offering is not null");
            // Check that student is not enrolled already
            var alreadyEnrolled = db.Enrolleds
                .Any(e => e.StudentId == uid && e.Class.Course.Department.SubjectAbbreviation == subject && e.Class.Course.Number == num &&
                        e.Class.SemesterSeason == season && e.Class.SemesterYear == year);

            if (alreadyEnrolled)
            {
                return Json(new { success = false });
            }

            // Update enrollment table
        
            db.Enrolleds.Add(new Enrolled
            {
                StudentId = uid,
                ClassId = courseOffering.ClassId
            });
            db.SaveChanges();
            
            return Json(new { success = true });
        }





        /// <summary>
        /// Calculates a student's GPA
        /// A student's GPA is determined by the grade-point representation of the average grade in all their classes.
        /// Assume all classes are 4 credit hours.
        /// If a student does not have a grade in a class ("--"), that class is not counted in the average.
        /// If a student is not enrolled in any classes, they have a GPA of 0.0.
        /// Otherwise, the point-value of a letter grade is determined by the table on this page:
        /// https://advising.utah.edu/academic-standards/gpa-calculator-new.php
        /// </summary>
        /// <param name="uid">The uid of the student</param>
        /// <returns>A JSON object containing a single field called "gpa" with the number value</returns>
        public IActionResult GetGPA(string uid)
        {
            var gradePoints = new Dictionary<string, double>
            {
                { "A", 4.0 },
                { "A-", 3.7 },
                { "B+", 3.3 },
                { "B", 3.0 },
                { "B-", 2.7 },
                { "C+", 2.3 },
                { "C", 2.0 },
                { "C-", 1.7 },
                { "D+", 1.3 },
                { "D", 1.0 },
                { "D-", 0.7 },
                { "F", 0.0 },
            };
            //Retrieve all grades for the given student (only those that are not null)
            var grades = db.Enrolleds
                .Where(e => e.StudentId == uid && e.Grade != "--" && e.Grade != null)
                .Select(e => e.Grade)
                .ToList();

            // Check if the student has any grades from their enrolled classes
            Console.WriteLine("KT Number of grades.Count: " + grades.Count);
            Console.WriteLine("KT Grades:");
            foreach (var grade in grades)
            {
                Console.WriteLine("KT " + grade);
            }
            /// If a student has no grades in any classes, they have a GPA of 0.0.
            if (grades.Count == 0)
            {
                return Json(new { gpa = 0.0 });
            }

            double totalPoints = 0.0;
            int countedClasses = 0;

            // Iterate through each enrollment to calculate the GPA
            foreach (var grade in grades)
            {
                // If the grade is not "--", calculate its point value
                if (!string.IsNullOrEmpty(grade) && gradePoints.ContainsKey(grade) )
                {
                    totalPoints += gradePoints[grade]; //assume all classes are 4 credits
                    countedClasses++;
                }
            }
            //gpa = gradePointScale * # hours/ total hours 
            double gpa = totalPoints/countedClasses; 

            return Json(new { gpa = gpa });
            //return Json("uncomment gpa stuff");
        }

        /*******End code to modify********/

    

    }
}

