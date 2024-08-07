using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Humanizer;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace LMS.Controllers
{
    public class AdministratorController : Controller
    {
        private readonly LMSContext db;

        public AdministratorController(LMSContext _db)
        {
            db = _db;
        }

        // GET: /<controller>/
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Department(string subject)
        {
            ViewData["subject"] = subject;
            return View();
        }

        public IActionResult Course(string subject, string num)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            return View();
        }

        /*******Begin code to modify********/

        /// <summary>
        /// Create a department which is uniquely identified by it's subject code
        /// </summary>
        /// <param name="subject">the subject code</param>
        /// <param name="name">the full name of the department</param>
        /// <returns>A JSON object containing {success = true/false}.
        /// false if the department already exists, true otherwise.</returns>
        public IActionResult CreateDepartment(string subject, string name)
        {
            // Check if the department already exists
            var existingDepartment = db.Departments.FirstOrDefault(d => d.SubjectAbbreviation == subject);

            if (existingDepartment != null)
            {
                return Json(new { success = false });
            }

            // Create a new department
            var newDepartment = new Department
            {
                SubjectAbbreviation = subject,
                Name = name
            };

            db.Departments.Add(newDepartment);
            db.SaveChanges();


            return Json(new { success = true });
        }


        /// <summary>
        /// Returns a JSON array of all the courses in the given department.
        /// Each object in the array should have the following fields:
        /// "number" - The course number (as in 5530)
        /// "name" - The course name (as in "Database Systems")
        /// </summary>
        /// <param name="subjCode">The department subject abbreviation (as in "CS")</param>
        /// <returns>The JSON result</returns>
        public IActionResult GetCourses(string subject)
        {
            
            
            var courses = db.Courses
                    .Where(c => c.Department.SubjectAbbreviation == subject)
                    .Select(c => new
                    {
                        number = c.Number,
                        name = c.Name
                    })
                    .ToList();
Console.WriteLine("TT entering get course");
            return Json(courses);
        }

        /// <summary>
        /// Returns a JSON array of all the professors working in a given department.
        /// Each object in the array should have the following fields:
        /// "lname" - The professor's last name
        /// "fname" - The professor's first name
        /// "uid" - The professor's uid
        /// </summary>
        /// <param name="subject">The department subject abbreviation</param>
        /// <returns>The JSON result</returns>
        public IActionResult GetProfessors(string subject)
        {

            var professors = db.Professors
                       .Where(p => p.Department.SubjectAbbreviation == subject)
                       .Select(p => new
                       {
                           lname = p.LastName,
                           fname = p.FirstName,
                           uid = p.ProfessorId
                       })
                       .ToList();
            
            return Json(professors);
            
        }



        /// <summary>
        /// Creates a course.
        /// A course is uniquely identified by its number + the subject to which it belongs
        /// </summary>
        /// <param name="subject">The subject abbreviation for the department in which the course will be added</param>
        /// <param name="number">The course number</param>
        /// <param name="name">The course name</param>
        /// <returns>A JSON object containing {success = true/false}.
        /// false if the course already exists, true otherwise.</returns>
        public IActionResult CreateCourse(string subject, int number, string name)
        {      

            

            // Check if the course already exists
            var existingCourse = db.Courses
                                .FirstOrDefault(c => c.Department.SubjectAbbreviation == subject && c.Number == number);

            if (existingCourse != null)
            {
                return Json(new { success = false });
            }
           

            // Get the department
            
            var department = db.Departments.FirstOrDefault(d => d.SubjectAbbreviation == subject);

            // if (department == null)
            // {
            //     return Json(new { success = false });
            // }

            // Create a new course
            var newCourse = new Course
            {
                DepartmentId = department.DepartmentId,
                Number = number,
                Name = name
            };

            Console.WriteLine("TT Adding Course");
            // Console.WriteLine("DepID is: " + department.DepartmentId + "")
            db.Courses.Add(newCourse);
            db.SaveChanges();

            
            return Json(new { success = true });
        }



        /// <summary>
        /// Creates a class offering of a given course.
        /// </summary>
        /// <param name="subject">The department subject abbreviation</param>
        /// <param name="number">The course number</param>
        /// <param name="season">The season part of the semester</param>
        /// <param name="year">The year part of the semester</param>
        /// <param name="start">The start time</param>
        /// <param name="end">The end time</param>
        /// <param name="location">The location</param>
        /// <param name="instructor">The uid of the professor</param>
        /// <returns>A JSON object containing {success = true/false}. 
        /// false if another class occupies the same location during any time 
        /// within the start-end range in the same semester, or if there is already
        /// a Class offering of the same Course in the same Semester,
        /// true otherwise.</returns>
        public IActionResult CreateClass(string subject, int number, string season, int year, DateTime start, DateTime end, string location, string instructor)
        {            
            // Find the course
            var course = db.Courses
                        .FirstOrDefault(c => c.Department.SubjectAbbreviation == subject && c.Number == number);

            if (course == null)
            {
                return Json(new { success = false });
            }

            //convert from dateTime to timeOnly
            TimeOnly startTime = TimeOnly.FromDateTime(start);
            TimeOnly endTime = TimeOnly.FromDateTime(end);

            // Check for time conflicts
            var conflicts = db.Classes
                            .Any(c => c.Location == location &&
                                        c.SemesterSeason == season &&
                                        c.SemesterYear == year &&
                                        ((c.StartTime <= startTime && c.EndTime >= startTime) ||
                                        (c.StartTime <= endTime && c.EndTime >= endTime) ||
                                        (c.StartTime >= startTime && c.EndTime <= endTime)));

            if (conflicts)
            {
                return Json(new { success = false });
            }

            // Create new class
            var newClass = new Class
            {
                CourseId = course.CourseId,
                SemesterSeason = season,
                SemesterYear = (uint)year,
                StartTime = startTime,
                EndTime = endTime,
                Location = location,
                ProfessorId = instructor
            };

            // Add and save changes
            db.Classes.Add(newClass);
            db.SaveChanges();


            return Json(new { success = true });
            
        }
            
        /*******End code to modify********/

    }
}

