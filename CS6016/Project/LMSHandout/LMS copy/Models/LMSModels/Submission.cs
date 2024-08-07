using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Submission
{
    public uint SubmitId { get; set; }

    public uint AssignmentId { get; set; }

    public string StudentId { get; set; } = null!;

    public DateTime? Time { get; set; }

    public ushort? Score { get; set; }

    public string? Contents { get; set; }

    public virtual Assignment Assignment { get; set; } = null!;

    public virtual Student Student { get; set; } = null!;
}
