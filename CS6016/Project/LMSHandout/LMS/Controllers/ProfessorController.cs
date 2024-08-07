using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace LMS_CustomIdentity.Controllers
{
    [Authorize(Roles = "Professor")]
    public class ProfessorController : Controller
    {

        private readonly LMSContext db;

        public ProfessorController(LMSContext _db)
        {
            db = _db;
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Students(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
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

        public IActionResult Categories(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            return View();
        }

        public IActionResult CatAssignments(string subject, string num, string season, string year, string cat)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
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

        public IActionResult Submissions(string subject, string num, string season, string year, string cat, string aname)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            return View();
        }

        public IActionResult Grade(string subject, string num, string season, string year, string cat, string aname, string uid)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            ViewData["uid"] = uid;
            return View();
        }

        /*******Begin code to modify********/


        /// <summary>
        /// Returns a JSON array of all the students in a class.
        /// Each object in the array should have the following fields:
        /// "fname" - first name
        /// "lname" - last name
        /// "uid" - user ID
        /// "dob" - date of birth
        /// "grade" - the student's grade in this class
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetStudentsInClass(string subject, int num, string season, int year)
        {
            Console.WriteLine("TT entering get students in class");
            var query = from s in db.Students
                       join e in db.Enrolleds on s.StudentId equals e.StudentId
                       join c in db.Classes on e.ClassId equals c.ClassId
                       join co in db.Courses on c.CourseId equals co.CourseId
                       where co.DepartmentId == (from d in db.Departments where d.SubjectAbbreviation == subject select d.DepartmentId).FirstOrDefault()
                             && co.Number == num
                             && c.SemesterSeason == season
                             && c.SemesterYear == year
                       select new
                       {
                           fname = s.FirstName,
                           lname = s.LastName,
                           uid = s.StudentId,
                           dob = s.Dob,
                           grade = e.Grade
                       };

                var students = query.ToArray();
                Console.WriteLine("TT size of students array" + students.Count());
                foreach (var student in students)
                {
                    Console.WriteLine("TT first name " + student.fname);
                }


            //    Console.WriteLine("TT first name "+ s.FirstName.Value);
            //    Console.WriteLine(string.Join(", ", (object[])query.ToArray()) + " TT");


           return Json(query.ToArray());

        }



        /// <summary>
        /// Returns a JSON array with all the assignments in an assignment category for a class.
        /// If the "category" parameter is null, return all assignments in the class.
        /// Each object in the array should have the following fields:
        /// "aname" - The assignment name
        /// "cname" - The assignment category name.
        /// "due" - The due DateTime
        /// "submissions" - The number of submissions to the assignment
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class, 
        /// or null to return assignments from all categories</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetAssignmentsInCategory(string subject, int num, string season, int year, string category)
{
    var query = from a in db.Assignments
                join ac in db.AssignmentCategories on a.CategoriesId equals ac.CategoriesId
                join c in db.Classes on ac.ClassId equals c.ClassId
                join co in db.Courses on c.CourseId equals co.CourseId
                join d in db.Departments on co.DepartmentId equals d.DepartmentId
                where d.SubjectAbbreviation == subject
                      && co.Number == num
                      && c.SemesterSeason == season
                      && c.SemesterYear == year
                      && (category == null || ac.CategoryName == category)
                select new
                {
                    aname = a.AssignmentName,
                    cname = ac.CategoryName,
                    due = a.Due,
                    submissions = db.Submissions.Count(s => s.AssignmentId == a.AssignmentId)
                };

    var assignments = query.ToArray();

    foreach (var assignment in assignments)
    {
        Console.WriteLine("aname is : " + assignment.aname);
    }

    return Json(assignments);
}



        /// <summary>
        /// Returns a JSON array of the assignment categories for a certain class.
        /// Each object in the array should have the folling fields:
        /// "name" - The category name
        /// "weight" - The category weight
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetAssignmentCategories(string subject, int num, string season, int year)
        {
            var query = from ac in db.AssignmentCategories
                       join c in db.Classes on ac.ClassId equals c.ClassId
                       join co in db.Courses on c.CourseId equals co.CourseId
                       where co.DepartmentId == (from d in db.Departments where d.SubjectAbbreviation == subject select d.DepartmentId).FirstOrDefault()
                             && co.Number == num
                             && c.SemesterSeason == season
                             && c.SemesterYear == year
                       select new
                       {
                           name = ac.CategoryName,
                           weight = ac.Weight
                       };


           return Json(query.ToArray());

        }

        /// <summary>
        /// Creates a new assignment category for the specified class.
        /// If a category of the given class with the given name already exists, return success = false.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The new category name</param>
        /// <param name="catweight">The new category weight</param>
        /// <returns>A JSON object containing {success = true/false} </returns>
        public IActionResult CreateAssignmentCategory(string subject, int num, string season, int year, string category, int catweight)
        {
            var classQuery = from c in db.Classes
                            join co in db.Courses on c.CourseId equals co.CourseId
                            where co.DepartmentId == (from d in db.Departments where d.SubjectAbbreviation == subject select d.DepartmentId).FirstOrDefault()
                                && co.Number == num
                                && c.SemesterSeason == season
                                && c.SemesterYear == year
                            select c.ClassId;


           var classId = classQuery.FirstOrDefault();


           if (classId == 0)
           {
               return Json(new { success = false });
           }


           var existingCategory = from ac in db.AssignmentCategories
                                  where ac.ClassId == classId && ac.CategoryName == category
                                  select ac;


           if (existingCategory.Any())
           {
               return Json(new { success = false });
           }


           AssignmentCategory newCategory = new AssignmentCategory
           {
               ClassId = classId,
               CategoryName = category,
               Weight = catweight
           };


           db.AssignmentCategories.Add(newCategory);
           db.SaveChanges();


           return Json(new { success = true });

        }

        /// <summary>
        /// Creates a new assignment for the given class and category.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The new assignment name</param>
        /// <param name="asgpoints">The max point value for the new assignment</param>
        /// <param name="asgdue">The due DateTime for the new assignment</param>
        /// <param name="asgcontents">The contents of the new assignment</param>
        /// <returns>A JSON object containing success = true/false</returns>
        public IActionResult CreateAssignment(string subject, int num, string season, int year, string category, string asgname, int asgpoints, DateTime asgdue, string asgcontents)
        {
            var classQuery = from c in db.Classes
                            join co in db.Courses on c.CourseId equals co.CourseId
                            where co.DepartmentId == (from d in db.Departments where d.SubjectAbbreviation == subject select d.DepartmentId).FirstOrDefault()
                                  && co.Number == num
                                  && c.SemesterSeason == season
                                  && c.SemesterYear == year
                            select c.ClassId;


           var classId = classQuery.FirstOrDefault();


           if (classId == 0)
               return Json(new { success = false });


           var categoryQuery = from ac in db.AssignmentCategories
                               where ac.ClassId == classId && ac.CategoryName == category
                               select ac.CategoriesId;


           var categoryId = categoryQuery.FirstOrDefault();


           if (categoryId == 0)
               return Json(new { success = false });


           Assignment newAssignment = new Assignment
           {
               AssignmentName = asgname,
               CategoriesId = categoryId,
               Points = (ushort)asgpoints,
               Due = asgdue,
               Instructions = asgcontents
           };


           db.Assignments.Add(newAssignment);
           db.SaveChanges();


           // Get all students enrolled in the class
            var enrolledStudents = db.Enrolleds.Where(e => e.ClassId == classId).ToList();

            // Loop through each student and update their overall grade
            foreach (var enrollment in enrolledStudents)
            {
                var updatedGrade = CalculateOverallGrade(enrollment.StudentId, classId);
                enrollment.Grade = updatedGrade;
            }

            db.SaveChanges();




           return Json(new { success = true });

        }


        /// <summary>
        /// Gets a JSON array of all the submissions to a certain assignment.
        /// Each object in the array should have the following fields:
        /// "fname" - first name
        /// "lname" - last name
        /// "uid" - user ID
        /// "time" - DateTime of the submission
        /// "score" - The score given to the submission
        /// 
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetSubmissionsToAssignment(string subject, int num, string season, int year, string category, string asgname)
        {
            var query = from s in db.Submissions
                       join a in db.Assignments on s.AssignmentId equals a.AssignmentId
                       join ac in db.AssignmentCategories on a.CategoriesId equals ac.CategoriesId
                       join c in db.Classes on ac.ClassId equals c.ClassId
                       join co in db.Courses on c.CourseId equals co.CourseId
                       join st in db.Students on s.StudentId equals st.StudentId
                       where co.DepartmentId == (from d in db.Departments where d.SubjectAbbreviation == subject select d.DepartmentId).FirstOrDefault()
                             && co.Number == num
                             && c.SemesterSeason == season
                             && c.SemesterYear == year
                             && ac.CategoryName == category
                             && a.AssignmentName == asgname
                       select new
                       {
                           fname = st.FirstName,
                           lname = st.LastName,
                           uid = st.StudentId,
                           time = s.Time,
                           score = s.Score
                       };


           return Json(query.ToArray());

        }


        /// <summary>
        /// Set the score of an assignment submission
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment</param>
        /// <param name="uid">The uid of the student who's submission is being graded</param>
        /// <param name="score">The new score for the submission</param>
        /// <returns>A JSON object containing success = true/false</returns>
        public IActionResult GradeSubmission(string subject, int num, string season, int year, string category, string asgname, string uid, int score)
        {
            Console.WriteLine("TT Entering GradeSubmitting");
            var submissionQuery = from s in db.Submissions
                                join a in db.Assignments on s.AssignmentId equals a.AssignmentId
                                join ac in db.AssignmentCategories on a.CategoriesId equals ac.CategoriesId
                                join c in db.Classes on ac.ClassId equals c.ClassId
                                join co in db.Courses on c.CourseId equals co.CourseId
                                where co.DepartmentId == (from d in db.Departments where d.SubjectAbbreviation == subject select d.DepartmentId).FirstOrDefault()
                                        && co.Number == num
                                        && c.SemesterSeason == season
                                        && c.SemesterYear == year
                                        && ac.CategoryName == category
                                        && a.AssignmentName == asgname
                                        && s.StudentId == uid
                                select s;

            var submission = submissionQuery.FirstOrDefault();
            
            Console.WriteLine("TT Submission null line");
            if (submission == null){
                Console.WriteLine(" TT submission == null error");
                return Json(new { success = false });
            }

            submission.Score = (ushort)score; // Explicitly cast int to ushort
            db.SaveChanges();

            // Calculate and update the student's overall grade
            var classId = (from c in db.Classes
                        join co in db.Courses on c.CourseId equals co.CourseId
                        where co.DepartmentId == (from d in db.Departments where d.SubjectAbbreviation == subject select d.DepartmentId).FirstOrDefault()
                                && co.Number == num
                                && c.SemesterSeason == season
                                && c.SemesterYear == year
                        select c.ClassId).FirstOrDefault();

                        // Console.WriteLine($"Parameters: subject={subject}, num={num}, season={season}, year={year}, category={category}, asgname={asgname}, uid={uid}, score={score} TT");


            var newGrade = CalculateOverallGrade(uid, classId);
            // UpdateOverallGrade(uid,classId);

            // Console.WriteLine("TT The new grade is : " + newGrade);

            var enrollment = db.Enrolleds.FirstOrDefault(e => e.StudentId == uid && e.ClassId == classId);
            if (enrollment != null)
            {
                enrollment.Grade = newGrade;
                db.SaveChanges();
            }

            return Json(new { success = true });
        }


        private void UpdateOverallGrade(string studentId, uint classId)
        {
            var overallGrade = CalculateOverallGrade(studentId, classId);
            Console.WriteLine("TT Updated Overall grade is : " + overallGrade);
            var enrollment = db.Enrolleds.FirstOrDefault(e => e.StudentId == studentId && e.ClassId == classId);
            if (enrollment != null)
            {
                enrollment.Grade = overallGrade;
                db.SaveChanges();
            }
        }

        private string CalculateOverallGrade(string studentId, uint classId)
        {
            // Load all assignment categories and assignments in memory to avoid multiple database queries
            var assignmentCategories = db.AssignmentCategories
                                        .Where(ac => ac.ClassId == classId)
                                        .ToList();

            var allAssignments = db.Assignments
                                .Where(a => assignmentCategories.Select(ac => ac.CategoriesId).Contains(a.CategoriesId))
                                .ToList();

            var allSubmissions = db.Submissions
                                .Where(s => s.StudentId == studentId && allAssignments.Select(a => a.AssignmentId).Contains(s.AssignmentId))
                                .ToList();

            double totalWeight = assignmentCategories.Sum(ac => (double)ac.Weight);
            double weightedScore = 0;

            foreach (var category in assignmentCategories)
            {
                var assignmentsInCategory = allAssignments.Where(a => a.CategoriesId == category.CategoriesId);

                double categoryTotalPoints = assignmentsInCategory.Sum(a => (double)a.Points);
                double categoryEarnedPoints = assignmentsInCategory
                    .Sum(a => {
                        var submission = allSubmissions.FirstOrDefault(s => s.AssignmentId == a.AssignmentId);
                        return submission != null ? (double)submission.Score : 0;
                    });

                Console.WriteLine("TT CategoryTotal Point is: " + categoryTotalPoints);
                Console.WriteLine("TT CategoryEarned Point is: " + categoryEarnedPoints);

                if (categoryTotalPoints > 0)
                {
                    double categoryPercentage = categoryEarnedPoints / categoryTotalPoints;
                    weightedScore += categoryPercentage * (double)category.Weight;
                }

                Console.WriteLine("TT WeightedScore of  "+ category.CategoryName + " is " + weightedScore);
                
            }
            

            double scalingFactor = 100 / totalWeight;
            double finalPercentage = totalWeight > 0 ? (weightedScore * scalingFactor) : 0;
            Console.WriteLine("TT Final Percentage : "+ finalPercentage);

            // Logic to convert percentage to a letter grade
            if (finalPercentage >= 90) return "A";
            if (finalPercentage >= 80) return "B";
            if (finalPercentage >= 70) return "C";
            if (finalPercentage >= 60) return "D";
            return "F";
        }




        /// <summary>
        /// Returns a JSON array of the classes taught by the specified professor
        /// Each object in the array should have the following fields:
        /// "subject" - The subject abbreviation of the class (such as "CS")
        /// "number" - The course number (such as 5530)
        /// "name" - The course name
        /// "season" - The season part of the semester in which the class is taught
        /// "year" - The year part of the semester in which the class is taught
        /// </summary>
        /// <param name="uid">The professor's uid</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetMyClasses(string uid)
        {            
            var query = from c in db.Classes
                       join co in db.Courses on c.CourseId equals co.CourseId
                       join p in db.Professors on c.ProfessorId equals p.ProfessorId
                       where p.ProfessorId == uid
                       select new
                       {
                           subject = (from d in db.Departments where d.DepartmentId == co.DepartmentId select d.SubjectAbbreviation).FirstOrDefault(),
                           number = co.Number,
                           name = co.Name,
                           season = c.SemesterSeason,
                           year = c.SemesterYear
                       };


           return Json(query.ToArray());

        }


        
        /*******End code to modify********/
    }
}

