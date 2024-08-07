using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using Pomelo.EntityFrameworkCore.MySql.Scaffolding.Internal;

namespace LMS.Models.LMSModels;

public partial class LMSContext : DbContext
{
    public LMSContext()
    {
    }

    public LMSContext(DbContextOptions<LMSContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Administrator> Administrators { get; set; }

    public virtual DbSet<Assignment> Assignments { get; set; }

    public virtual DbSet<AssignmentCategory> AssignmentCategories { get; set; }

    public virtual DbSet<Class> Classes { get; set; }

    public virtual DbSet<Course> Courses { get; set; }

    public virtual DbSet<Department> Departments { get; set; }

    public virtual DbSet<Enrolled> Enrolleds { get; set; }

    public virtual DbSet<Professor> Professors { get; set; }

    public virtual DbSet<Student> Students { get; set; }

    public virtual DbSet<Submission> Submissions { get; set; }

    public virtual DbSet<User> Users { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        => optionsBuilder.UseMySql("name=LMS:LMSConnectionString", Microsoft.EntityFrameworkCore.ServerVersion.Parse("10.11.8-mariadb"));

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder
            .UseCollation("latin1_swedish_ci")
            .HasCharSet("latin1");

        modelBuilder.Entity<Administrator>(entity =>
        {
            entity.HasKey(e => e.AdminId).HasName("PRIMARY");

            entity.Property(e => e.AdminId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("adminID");
            entity.Property(e => e.Dob).HasColumnName("dob");
            entity.Property(e => e.FirstName)
                .HasMaxLength(100)
                .HasColumnName("firstName");
            entity.Property(e => e.LastName)
                .HasMaxLength(100)
                .HasColumnName("lastName");

            entity.HasOne(d => d.Admin).WithOne(p => p.Administrator)
                .HasForeignKey<Administrator>(d => d.AdminId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Administrators_ibfk_1");
        });

        modelBuilder.Entity<Assignment>(entity =>
        {
            entity.HasKey(e => e.AssignmentId).HasName("PRIMARY");

            entity.HasIndex(e => new { e.CategoriesId, e.AssignmentName }, "categoriesID").IsUnique();

            entity.Property(e => e.AssignmentId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("assignmentID");
            entity.Property(e => e.AssignmentName)
                .HasMaxLength(100)
                .HasColumnName("assignment_name");
            entity.Property(e => e.CategoriesId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("categoriesID");
            entity.Property(e => e.Due)
                .HasColumnType("datetime")
                .HasColumnName("due");
            entity.Property(e => e.Instructions)
                .HasColumnType("mediumtext")
                .HasColumnName("instructions");
            entity.Property(e => e.Points)
                .HasColumnType("smallint(5) unsigned")
                .HasColumnName("points");

            entity.HasOne(d => d.Categories).WithMany(p => p.Assignments)
                .HasForeignKey(d => d.CategoriesId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Assignments_ibfk_1");
        });

        modelBuilder.Entity<AssignmentCategory>(entity =>
        {
            entity.HasKey(e => e.CategoriesId).HasName("PRIMARY");

            entity.HasIndex(e => new { e.ClassId, e.CategoryName }, "classID").IsUnique();

            entity.Property(e => e.CategoriesId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("categoriesID");
            entity.Property(e => e.CategoryName)
                .HasMaxLength(100)
                .HasColumnName("category_name");
            entity.Property(e => e.ClassId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("classID");
            entity.Property(e => e.Weight)
                .HasPrecision(5, 2)
                .HasColumnName("weight");

            entity.HasOne(d => d.Class).WithMany(p => p.AssignmentCategories)
                .HasForeignKey(d => d.ClassId)
                .HasConstraintName("AssignmentCategories_ibfk_1");
        });

        modelBuilder.Entity<Class>(entity =>
        {
            entity.HasKey(e => e.ClassId).HasName("PRIMARY");

            entity.HasIndex(e => e.CourseId, "courseID");

            entity.HasIndex(e => e.ProfessorId, "professorID");

            entity.HasIndex(e => new { e.SemesterYear, e.SemesterSeason, e.CourseId }, "semester_year").IsUnique();

            entity.Property(e => e.ClassId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("classID");
            entity.Property(e => e.CourseId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("courseID");
            entity.Property(e => e.EndTime)
                .HasColumnType("time")
                .HasColumnName("end_time");
            entity.Property(e => e.Location)
                .HasMaxLength(100)
                .HasColumnName("location");
            entity.Property(e => e.ProfessorId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("professorID");
            entity.Property(e => e.SemesterSeason)
                .HasColumnType("enum('Spring','Fall','Summer')")
                .HasColumnName("semester_season");
            entity.Property(e => e.SemesterYear)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("semester_year");
            entity.Property(e => e.StartTime)
                .HasColumnType("time")
                .HasColumnName("start_time");

            entity.HasOne(d => d.Course).WithMany(p => p.Classes)
                .HasForeignKey(d => d.CourseId)
                .HasConstraintName("Classes_ibfk_1");

            entity.HasOne(d => d.Professor).WithMany(p => p.Classes)
                .HasForeignKey(d => d.ProfessorId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Classes_ibfk_2");
        });

        modelBuilder.Entity<Course>(entity =>
        {
            entity.HasKey(e => e.CourseId).HasName("PRIMARY");

            entity.HasIndex(e => new { e.DepartmentId, e.Number }, "departmentID").IsUnique();

            entity.Property(e => e.CourseId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("courseID");
            entity.Property(e => e.DepartmentId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("departmentID");
            entity.Property(e => e.Name)
                .HasMaxLength(100)
                .HasColumnName("name");
            entity.Property(e => e.Number)
                .HasColumnType("int(10)")
                .HasColumnName("number");

            entity.HasOne(d => d.Department).WithMany(p => p.Courses)
                .HasForeignKey(d => d.DepartmentId)
                .HasConstraintName("Courses_ibfk_1");
        });

        modelBuilder.Entity<Department>(entity =>
        {
            entity.HasKey(e => e.DepartmentId).HasName("PRIMARY");

            entity.HasIndex(e => e.SubjectAbbreviation, "subject_abbreviation").IsUnique();

            entity.Property(e => e.DepartmentId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("departmentID");
            entity.Property(e => e.Name)
                .HasMaxLength(100)
                .HasColumnName("name");
            entity.Property(e => e.SubjectAbbreviation)
                .HasMaxLength(4)
                .IsFixedLength()
                .HasColumnName("subject_abbreviation");
        });

        modelBuilder.Entity<Enrolled>(entity =>
        {
            entity.HasKey(e => new { e.StudentId, e.ClassId })
                .HasName("PRIMARY")
                .HasAnnotation("MySql:IndexPrefixLength", new[] { 0, 0 });

            entity.ToTable("Enrolled");

            entity.HasIndex(e => e.ClassId, "classID");

            entity.Property(e => e.StudentId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("studentID");
            entity.Property(e => e.ClassId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("classID");
            entity.Property(e => e.Grade)
                .HasMaxLength(2)
                .IsFixedLength()
                .HasColumnName("grade");

            entity.HasOne(d => d.Class).WithMany(p => p.Enrolleds)
                .HasForeignKey(d => d.ClassId)
                .HasConstraintName("Enrolled_ibfk_2");

            entity.HasOne(d => d.Student).WithMany(p => p.Enrolleds)
                .HasForeignKey(d => d.StudentId)
                .HasConstraintName("Enrolled_ibfk_1");
        });

        modelBuilder.Entity<Professor>(entity =>
        {
            entity.HasKey(e => e.ProfessorId).HasName("PRIMARY");

            entity.HasIndex(e => e.DepartmentId, "departmentID");

            entity.Property(e => e.ProfessorId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("professorID");
            entity.Property(e => e.DepartmentId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("departmentID");
            entity.Property(e => e.Dob).HasColumnName("dob");
            entity.Property(e => e.FirstName)
                .HasMaxLength(100)
                .HasColumnName("firstName");
            entity.Property(e => e.LastName)
                .HasMaxLength(100)
                .HasColumnName("lastName");

            entity.HasOne(d => d.Department).WithMany(p => p.Professors)
                .HasForeignKey(d => d.DepartmentId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Professors_ibfk_2");

            entity.HasOne(d => d.ProfessorNavigation).WithOne(p => p.Professor)
                .HasForeignKey<Professor>(d => d.ProfessorId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Professors_ibfk_1");
        });

        modelBuilder.Entity<Student>(entity =>
        {
            entity.HasKey(e => e.StudentId).HasName("PRIMARY");

            entity.HasIndex(e => e.MajorId, "majorID");

            entity.Property(e => e.StudentId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("studentID");
            entity.Property(e => e.Dob).HasColumnName("dob");
            entity.Property(e => e.FirstName)
                .HasMaxLength(100)
                .HasColumnName("firstName");
            entity.Property(e => e.LastName)
                .HasMaxLength(100)
                .HasColumnName("lastName");
            entity.Property(e => e.MajorId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("majorID");

            entity.HasOne(d => d.Major).WithMany(p => p.Students)
                .HasForeignKey(d => d.MajorId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Students_ibfk_2");

            entity.HasOne(d => d.StudentNavigation).WithOne(p => p.Student)
                .HasForeignKey<Student>(d => d.StudentId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Students_ibfk_1");
        });

        modelBuilder.Entity<Submission>(entity =>
        {
            entity.HasKey(e => e.SubmitId).HasName("PRIMARY");

            entity.HasIndex(e => e.AssignmentId, "assignmentID");

            entity.HasIndex(e => new { e.StudentId, e.AssignmentId, e.Time }, "studentID").IsUnique();

            entity.Property(e => e.SubmitId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("submit_ID");
            entity.Property(e => e.AssignmentId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("assignmentID");
            entity.Property(e => e.Contents)
                .HasColumnType("mediumtext")
                .HasColumnName("contents");
            entity.Property(e => e.Score)
                .HasColumnType("smallint(5) unsigned")
                .HasColumnName("score");
            entity.Property(e => e.StudentId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("studentID");
            entity.Property(e => e.Time)
                .HasColumnType("datetime")
                .HasColumnName("time");

            entity.HasOne(d => d.Assignment).WithMany(p => p.Submissions)
                .HasForeignKey(d => d.AssignmentId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Submissions_ibfk_2");

            entity.HasOne(d => d.Student).WithMany(p => p.Submissions)
                .HasForeignKey(d => d.StudentId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Submissions_ibfk_1");
        });

        modelBuilder.Entity<User>(entity =>
        {
            entity.HasKey(e => e.UId).HasName("PRIMARY");

            entity.Property(e => e.UId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("uID");
            entity.Property(e => e.Dob).HasColumnName("dob");
            entity.Property(e => e.FirstName)
                .HasMaxLength(100)
                .HasColumnName("firstName");
            entity.Property(e => e.LastName)
                .HasMaxLength(100)
                .HasColumnName("lastName");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
