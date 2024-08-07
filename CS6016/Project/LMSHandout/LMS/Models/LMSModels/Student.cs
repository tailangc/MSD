using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Student
{
    public string StudentId { get; set; } = null!;

    public string? FirstName { get; set; }

    public string? LastName { get; set; }

    public DateOnly? Dob { get; set; }

    public uint MajorId { get; set; }

    public virtual ICollection<Enrolled> Enrolleds { get; set; } = new List<Enrolled>();

    public virtual Department Major { get; set; } = null!;

    public virtual User StudentNavigation { get; set; } = null!;

    public virtual ICollection<Submission> Submissions { get; set; } = new List<Submission>();
}
