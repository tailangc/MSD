using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Assignment
{
    public uint AssignmentId { get; set; }

    public uint CategoriesId { get; set; }

    public string? AssignmentName { get; set; }

    public DateTime? Due { get; set; }

    public ushort? Points { get; set; }

    public string? Instructions { get; set; }

    public virtual AssignmentCategory Categories { get; set; } = null!;

    public virtual ICollection<Submission> Submissions { get; set; } = new List<Submission>();
}
