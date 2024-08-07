using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Class
{
    public uint ClassId { get; set; }

    public uint CourseId { get; set; }

    public string ProfessorId { get; set; } = null!;

    public uint? SemesterYear { get; set; }

    public string? SemesterSeason { get; set; }

    public string? Location { get; set; }

    public TimeOnly? StartTime { get; set; }

    public TimeOnly? EndTime { get; set; }

    public virtual ICollection<AssignmentCategory> AssignmentCategories { get; set; } = new List<AssignmentCategory>();

    public virtual Course Course { get; set; } = null!;
   

    public virtual ICollection<Enrolled> Enrolleds { get; set; } = new List<Enrolled>();

    public virtual Professor Professor { get; set; } = null!;
}
